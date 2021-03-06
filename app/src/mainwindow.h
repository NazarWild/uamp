#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QFileSystemModel>
#include <QApplication>
#include <QMessageBox>
#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QStringList>
#include <QModelIndex>
#include <QResizeEvent>
#include <QDebug>
#include <QFileInfo>
#include <QPlainTextEdit>
#include <QPalette>
#include <QLabel>
#include <QMediaPlayer>
#include <QtSql>
#include <QAbstractItemView>
#include <QSqlTableModel>
#include <QMediaPlaylist>
#include <QFileInfo>

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <QVector>

#include <tag.h>
#include <tagutils.h>
#include <tagunion.h>
#include <fileref.h>
#include <taglib_export.h>
#include <audioproperties.h>

#include "recentlyused.h"
#include "playlists.h"
#include "Player.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString rightTimeChange(int sec);

    void openMusicFile();

    void setMusicInfo();

    //databases part
    void creationOfTables();

    void insertIntoMusicInfo();

    void insertIntoListSidPid();

    QString createFilter();
    
    void show_table();

    void insertSettInfo(); //cur song + recently used
    
    void insertRecentlyUsed(); //recently used
    
    void dataRecovery();
    //Playlist
    void addGeneral();
    //
    void setCurSid();

    bool sidInPidIsUnique();

    void addToQueue();

private slots: // all actions 
    void on_actionOpen_Folder_triggered(); 

    void on_actionOpen_File_triggered();

    void currentMusicTableIndex(const QModelIndex &index);

    void elementClicked(const QModelIndex& current);

    void on_editTableModel_clicked(int, QSqlRecord &);

    void on_actionRecently_opened_triggered();

    void onLibraryContextMenu(const QPoint &point);

    void onTableContextMenu(const QPoint &point);

    void onQueueContextMenu(const QPoint &point);

    void addToPlaylist();
    
    void on_playlists_clicked();

    void changePlaylist(int pid);

    void setDir(QString dir);

    void funcForDelete();

    void deleteQueueElement();

    void on_actionFast_triggered();

    void on_actionFast_Rewind_triggered();

private:
    Ui::MainWindow *ui;
    QString m_path_file;
    QString m_path_dir;
    QFileSystemModel *m_model;
    QSqlDatabase m_db;
    QSqlTableModel *m_sqlModel;
    QModelIndex m_table_index;
private:
    QVector<QString> m_queue;
    QStringList m_allowedTypes = {"*.mp3", "*.m4a", "*.wav", "*.mp4"};
    QString m_cur_title;
    QString m_cur_duration;
    QString m_cur_artist;
    QString m_cur_album;
    QString m_cur_genre;
    int m_cur_pid;
    int m_cur_sid;
private:
    RecentlyUsed *m_recently_used_win;
    Playlists *m_playlists_win;
    Player *m_player;
};
