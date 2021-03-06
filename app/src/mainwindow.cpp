#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Player.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow),
    m_model(new QFileSystemModel(this)),
    m_db(QSqlDatabase::addDatabase("QSQLITE")),
    m_sqlModel(new QSqlTableModel),
    m_recently_used_win(new RecentlyUsed),
    m_playlists_win(new Playlists)
{
    ui->setupUi(this);

    m_cur_pid = 1;
    m_cur_sid = 0;

    m_player = new Player(this, ui);

    m_db.setHostName("localhost");
    m_db.setDatabaseName("databaseUamp");
    bool ok = m_db.open();

    if (ok) {
        creationOfTables();
        dataRecovery();
        show_table();
    }
    if(!m_path_dir.isEmpty()) {
        m_model->setRootPath(m_path_dir);
        m_model->setNameFilters(m_allowedTypes);
        ui->treeView->setRootIndex(m_model->index(m_path_dir));
    }
    ui->treeView->setModel(m_model);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->setSelectionBehavior (QAbstractItemView::SelectRows);

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(onLibraryContextMenu(const QPoint &)));

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(onTableContextMenu(const QPoint &)));

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(onQueueContextMenu(const QPoint &)));

    QPixmap pix("./app/resources/music_anonim.svg");
    int w = ui->albumImage->width();
    int h = ui->albumImage->height();

    ui->albumImage->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
    ui->playButton->setIcon(QIcon("./app/resources/playButton.svg"));
    ui->previousButton->setIcon(QIcon("./app/resources/previousButton.svg"));
    ui->nextButton->setIcon(QIcon("./app/resources/nextButton.svg"));
    ui->playlists->setIcon(QIcon("./app/resources/headphones.svg"));

    for (int i = 1; i < m_model->columnCount(); i++)
        ui->treeView->hideColumn(i);

    connect(ui->treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(elementClicked(QModelIndex)));
    connect(ui->tableView, &QAbstractItemView::clicked, this, &MainWindow::currentMusicTableIndex);
    connect(m_sqlModel, &QSqlTableModel::beforeUpdate, this, &MainWindow::on_editTableModel_clicked);
    connect(m_playlists_win, SIGNAL(changePlaylistSig(int)), this, SLOT(changePlaylist(int)));
    connect(m_recently_used_win, SIGNAL(selectDir(QString)), this, SLOT(setDir(QString)));
}

MainWindow::~MainWindow()
{
    m_db.close();
    delete m_model;
    delete m_sqlModel;
    delete m_playlists_win;
    delete m_recently_used_win;
    delete ui;
}

QString MainWindow::rightTimeChange(int sec) {
    QString first = QString::number(sec / 60);
    QString second = QString::number(sec % 60);

    if (second.length() == 1)
        second = "0" + second;
    return first + ":" + second;
}

void MainWindow::openMusicFile() {
    if(!m_path_file.isEmpty()) {
        TagLib::FileRef f(m_path_file.toStdString().c_str());

        if(f.file()->isValid()) {

            setMusicInfo();
            ui->trackName->setText(m_cur_title);
            ui->authorName->setText(m_cur_artist);
        }
    }
}

void MainWindow::setMusicInfo() {
    if(!m_path_file.isEmpty()) {
        TagLib::FileRef f(m_path_file.toStdString().c_str());

        if(f.file()->isValid()) {
            int sec = f.audioProperties()->lengthInSeconds();

            m_cur_title = TStringToQString(f.tag()->title());
            m_cur_duration = rightTimeChange(sec);
            m_cur_artist = TStringToQString(f.tag()->artist());
            m_cur_album = TStringToQString(f.tag()->album());
            m_cur_genre = TStringToQString(f.tag()->genre());
        }
    }
}

void MainWindow::creationOfTables() {
    QSqlQuery query;
    query.exec("CREATE TABLE music_info (sid INTEGER PRIMARY KEY AUTOINCREMENT,Title TEXT, Duration TEXT, Artist TEXT, Album TEXT, Genre TEXT, Rating INTEGER, Played INTEGER, Path TEXT NOT NULL UNIQUE);");
    query.exec("CREATE TABLE setting_info (curSong TEXT, recentlyUsed TEXT);");
    query.exec("CREATE TABLE recentlyUsed (Path TEXT NOT NULL UNIQUE);");
    query.exec("CREATE TABLE Playlists (pid INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT NOT NULL UNIQUE);");
    addGeneral();
    query.exec("PRAGMA foreign_keys = ON;");
    QString str = "CREATE TABLE List_sid_pid ("  \
      "ID            INTEGER  PRIMARY KEY  AUTOINCREMENT," \
      "pid    INTEGER  NOT NULL," \
      "sid        INTEGER  NOT NULL," \
      "FOREIGN KEY (pid) REFERENCES Playlists (pid)" \
      "FOREIGN KEY (sid) REFERENCES music_info (sid) ON DELETE CASCADE" \
      ");";
    query.exec(str);
}

void MainWindow::insertIntoMusicInfo() {
    QSqlQuery query;
    query.prepare("INSERT INTO music_info (Title, Duration, Artist, Album, Genre, Rating, Played, Path) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.bindValue(0, m_cur_title);
    query.bindValue(1, m_cur_duration);
    query.bindValue(2, m_cur_artist);
    query.bindValue(3, m_cur_album);
    query.bindValue(4, m_cur_genre);
    query.bindValue(5, 0);
    query.bindValue(6, 0);
    query.bindValue(7, m_path_file);
    query.exec();
    show_table();
}

void MainWindow::insertIntoListSidPid() {
    QSqlQuery query;
    query.prepare("INSERT INTO List_sid_pid (pid, sid) "
                  "VALUES (?, ?)");
    query.bindValue(0, m_cur_pid);
    query.bindValue(1, m_cur_sid);
    query.exec();
}

QString MainWindow::createFilter() {
    QString filter = "sid IN (";
    QString query = "SELECT sid FROM List_sid_pid WHERE pid = ";
    QSqlQueryModel model;
    query += QString::number(m_cur_pid);

    model.setQuery(query);
    for (int i = 0; i < model.rowCount(); i++) {
        if (i < model.rowCount() - 1) {
            filter += QString::number(model.record(i).value("sid").toInt());
            filter += ", ";
        }
        else {
            filter += QString::number(model.record(i).value("sid").toInt());
            filter += ")";
        }
    }
    return filter;
}

void MainWindow::show_table() {
    QString filter = createFilter();

    m_sqlModel->setTable("music_info");
    m_sqlModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_sqlModel->setFilter(filter);
    m_sqlModel->select();

    ui->tableView->verticalHeader()->hide();
    ui->tableView->setModel(m_sqlModel);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(2, 70);
    ui->tableView->setColumnWidth(3, 150);
    ui->tableView->setColumnWidth(4, 177);
    ui->tableView->setColumnWidth(5, 80);
    ui->tableView->setColumnWidth(6, 50);
    ui->tableView->setColumnWidth(8, 165);
    ui->tableView->hideColumn(0); // don't show ID's
    ui->tableView->hideColumn(7); // not ready Played column
    ui->tableView->show();
}

void MainWindow::insertSettInfo() {
    QSqlQuery query;
    query.prepare("INSERT INTO setting_info (curSong, recentlyUsed) "
                  "VALUES (?, ?)");
    query.bindValue(0, m_path_file);
    query.bindValue(1, m_path_dir);
    query.exec();
}

void MainWindow::insertRecentlyUsed() {
    QSqlQuery query;
    query.prepare("INSERT INTO recentlyUsed (Path) "
                  "VALUES (?)");
    query.bindValue(0, m_path_dir);
    query.exec();
}

void MainWindow::dataRecovery() {
    QSqlQueryModel model;
    model.setQuery("SELECT curSong, recentlyUsed FROM setting_info");
    m_path_file = model.record(model.rowCount() - 1).value("curSong").toString();
    m_path_dir = model.record(model.rowCount() - 1).value("recentlyUsed").toString();

    if(!m_path_dir.isEmpty() && QFileInfo::exists(m_path_dir)) {
        m_model->setRootPath(m_path_dir);
        ui->treeView->setModel(m_model);
    }
    model.setQuery("SELECT Name FROM Playlists");
}

void MainWindow::addGeneral() {
    QSqlQuery query;
    query.prepare("INSERT INTO Playlists (Name) "
                  "VALUES (?)");
    query.bindValue(0, "General");
    query.exec();
}

void MainWindow::setCurSid() {
    QSqlQueryModel model;
    QString zapros = "SELECT sid FROM music_info WHERE Path LIKE '";
    zapros += m_path_file;
    zapros += "'";
    model.setQuery(zapros);
    m_cur_sid = model.record(model.rowCount() - 1).value("sid").toInt();
}

bool MainWindow::sidInPidIsUnique() {
    QSqlQueryModel model;

    model.setQuery("SELECT sid, pid FROM List_sid_pid");
    for (int i = 0; i < model.rowCount(); i++) {
        if ((model.record(i).value("pid").toInt() == m_cur_pid) 
            && (model.record(i).value("sid").toInt() == m_cur_sid)) {
            return false;
        }
    }
    return true;    
}

void MainWindow::addToQueue() {
	if (!m_queue.contains(m_cur_title)) {
		m_queue.push_back(m_cur_title);

    	ui->listWidget->addItem(m_cur_title);

    	m_player->addToPlaylist({QUrl::fromLocalFile(m_path_file)});
	}
}

//private slots

void MainWindow::on_actionOpen_Folder_triggered()
{
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath()); 
    dialog.setFileMode(QFileDialog::Directory);
    QString dirname = dialog.getExistingDirectory();

    if (dirname.isEmpty())
        return;
    m_path_dir = dirname;
    m_path_file.clear();

    insertRecentlyUsed();
    insertSettInfo();
    m_model->setRootPath(m_path_dir);
    m_model->setNameFilters(m_allowedTypes);
    ui->treeView->setRootIndex(m_model->index(m_path_dir));
}

void MainWindow::on_actionOpen_File_triggered() {
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath()); 
    dialog.setFileMode(QFileDialog::Directory);
    QString filename = dialog.getOpenFileName();

    QFile file(filename);
    QFileInfo info(filename);
    QString extension = info.suffix();

    if (file.open(QFile::ReadOnly | QFile::Text) && (extension == "mp3" || extension == "mp4" || extension == "wav" || extension == "m4a")) {

        m_path_file = filename;
        QFileInfo fileInfo(filename);
        m_path_dir = fileInfo.dir().absolutePath();

        insertRecentlyUsed();
        insertSettInfo();
        openMusicFile();
        addToQueue();
        m_model->setRootPath(m_path_dir);
        m_model->setNameFilters(m_allowedTypes);
        ui->treeView->setRootIndex(m_model->index(m_path_dir));
    }
}

void MainWindow::currentMusicTableIndex(const QModelIndex &index) {
    m_table_index = index;
}

void MainWindow::elementClicked(const QModelIndex& current) {
    QModelIndex p = current;
    std::vector<QString> vec;
    QString tmp_path;

    while(p.isValid()) {
        vec.push_back(p.data().toString());
        p = p.parent();
    }
    std::reverse(vec.begin(), vec.end());
    for (const auto& i : vec) {
        if (i.toStdString() != "/")
            tmp_path += "/" + i;
    }

    QFileInfo info(tmp_path);
    QString extension = info.suffix();
    if (info.isFile() && (extension == "mp3" || extension == "mp4" || extension == "wav" || extension == "m4a")){
        m_path_file = tmp_path;
        insertSettInfo();
        openMusicFile();
        addToQueue();
    }
}

void MainWindow::on_editTableModel_clicked(int, QSqlRecord &) {
    QString path = m_sqlModel->record(m_table_index.row()).value("Path").toString();
    TagLib::FileRef f(path.toStdString().c_str());

    if(f.file()->isValid()) {
        QString buffer = m_sqlModel->record(m_table_index.row()).value("Title").toString();
        f.tag()->setTitle(buffer.toStdString());
        buffer = m_sqlModel->record(m_table_index.row()).value("Artist").toString();
        f.tag()->setArtist(buffer.toStdString());
        buffer = m_sqlModel->record(m_table_index.row()).value("Album").toString();
        f.tag()->setAlbum(buffer.toStdString());
        buffer = m_sqlModel->record(m_table_index.row()).value("Genre").toString();
        f.tag()->setGenre(buffer.toStdString());
        f.save();
    }
}

void MainWindow::on_actionRecently_opened_triggered() {
    QSqlTableModel *sqlModel = new QSqlTableModel;

    sqlModel->setTable("recentlyUsed");
    sqlModel->select();

    m_recently_used_win->setModel(sqlModel);
    m_recently_used_win->move(pos().x() - 400, pos().y());
    m_recently_used_win->show();
}

void MainWindow::onLibraryContextMenu(const QPoint &point)
{
    QModelIndex p = ui->treeView->currentIndex();
    std::vector<QString> vec;
    QString tmp_path;

    while(p.isValid()) {
        vec.push_back(p.data().toString());
        p = p.parent();
    }
    std::reverse(vec.begin(), vec.end());
    for (const auto& i : vec) {
        if (i.toStdString() != "/")
            tmp_path += "/" + i;
    }
    m_path_file = tmp_path;

    QMenu contextMenu(tr("SideBar context menu"), this);

    QAction action_open("Open folder", this);
    connect(&action_open, &QAction::triggered, this, &MainWindow::on_actionOpen_Folder_triggered);
    contextMenu.addAction(&action_open);

    QAction action_new("Add to playlist", this);
    connect(&action_new, &QAction::triggered, this, &MainWindow::addToPlaylist);
    contextMenu.addAction(&action_new);

    contextMenu.exec(ui->treeView->viewport()->mapToGlobal(point));
}

void MainWindow::onTableContextMenu(const QPoint &point)
{
    QMenu contextMenu(tr("SideBar context menu"), this);

    QAction action_delete("Delete from playlist", this);
    connect(&action_delete, &QAction::triggered, this, &MainWindow::funcForDelete);
    contextMenu.addAction(&action_delete);

    contextMenu.exec(ui->tableView->viewport()->mapToGlobal(point));
}

void MainWindow::onQueueContextMenu(const QPoint &point)
{
    QMenu contextMenu(tr("SideBar context menu"), this);

    QAction action_delete("Delete from queue", this);
    connect(&action_delete, &QAction::triggered, this, &MainWindow::deleteQueueElement);
    contextMenu.addAction(&action_delete);

    contextMenu.exec(ui->listWidget->viewport()->mapToGlobal(point));
}

///////////////////////////////////////////////////////////////////////////
void MainWindow::addToPlaylist() {
    if (!m_path_file.isEmpty()) {
        setMusicInfo();
        insertIntoMusicInfo();
        setCurSid();
        if (sidInPidIsUnique())
            insertIntoListSidPid();
        show_table();
    }
}
///////////////////////////////////////////////////////////////////////////

void MainWindow::on_playlists_clicked() {
    m_playlists_win->clearAll();
    m_playlists_win->dataRecovery();
    m_playlists_win->insertNameOfPlaylist();
    m_playlists_win->move(1852, pos().y());
    m_playlists_win->show();
}

void MainWindow::changePlaylist(int pid) {
    m_cur_pid = pid;
    show_table();
}

void MainWindow::setDir(QString dir) {
    m_path_dir = dir;
    m_model->setRootPath(m_path_dir);
    ui->treeView->setRootIndex(m_model->index(m_path_dir));
}

void MainWindow::funcForDelete() {
    QString path = m_sqlModel->record(m_table_index.row()).value("Path").toString();
    QSqlQuery query;
    QString str = "DELETE FROM music_info WHERE Path LIKE '";
    str += path;
    str += "'";
    query.exec(str);
    show_table();
}

void MainWindow::deleteQueueElement() {
    QModelIndex p = ui->listWidget->currentIndex();
    m_player->deleteFromPlaylist(p.row());

    qDebug() << p.data().toString() << " " << p.row();
    m_queue.removeOne(p.data().toString());
    ui->listWidget->clear();
    for (auto item : m_queue)
        ui->listWidget->addItem(item);
}

void MainWindow::on_actionFast_triggered()
{
    int pos = m_player->m_player->position();
    pos += 10 * 1000;
    m_player->m_player->setPosition(pos);
}

void MainWindow::on_actionFast_Rewind_triggered()
{
    int pos = m_player->m_player->position();
    pos += -10 * 1000;
    m_player->m_player->setPosition(pos);
}
