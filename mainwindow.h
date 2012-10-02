#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class QAction;
class QMenu;
class QTextEdit;
class QProcess;
class PreviewWidget;
class QTimer;
class QLabel;
class QSignalMapper;
class QToolBox;
class QListWidget;
class QListWidgetItem;
class FileCache;
class RecentDocuments;
class QSignalMapper;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openDocument(const QString& path);

public slots:
    void newDocument();

private slots:
    void about();
    void refresh(bool forced = false);
    void refreshFinished();
    void changeImageFormat();
    void undo();
    void redo();

    void onAutoRefreshActionToggled(bool state);
    void onEditorChanged();
    void onRefreshActionTriggered();
    void onPreferencesActionTriggered();
    void onOpenDocumentActionTriggered();
    void onSaveActionTriggered();
    void onSaveAsActionTriggered();
    void onExportImageActionTriggered();
    void onExportAsImageActionTriggered();
    void onRecentDocumentsActionTriggered(const QString& path);
    void onAssistanItemClicked(QListWidgetItem* item);
    void onAssistanItemDoubleClicked(QListWidgetItem* item);
    void onSingleApplicationReceivedMessage(const QString& message);
    void onAssistantFocus();
    void onAssistantItemPreview(QWidget* widget);
    void onAssistantItemInsert(QWidget* widget);
    void onNextAssistant();
    void onPrevAssistant();

private:
    enum ImageFormat { SvgFormat, PngFormat };

    void closeEvent(QCloseEvent *event);

    bool maybeSave();
    void readSettings();
    void writeSettings();
    bool saveDocument(const QString& name);
    void exportImage(const QString& name);
    QString makeKeyForDocument(QByteArray current_document);

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void enableUndoRedoActions();

    void checkPaths();
    void reloadAssistantXml(const QString& path);
    void insertAssistantCode(const QString& code);

    bool refreshFromCache();
    void updateCacheSizeInfo();

    QLabel *m_currentImageFormatLabel;
    QLabel *m_autoRefreshLabel;
    QLabel *m_exportPathLabel;
    QLabel *m_cacheSizeLabel;

    QString m_documentPath;
    QString m_exportPath;
    QString m_lastKey;
    QByteArray m_cachedImage;

    QString m_assistantXmlPath;
    QList<QListWidget*> m_assistantWidgets;

    bool m_useCustomJava;
    bool m_useCustomPlantUml;
    bool m_useCustomGraphiz;
    bool m_useCache;
    bool m_useCustomCache;
    int m_cacheMaxSize;

    QString m_javaPath;
    QString m_plantUmlPath;
    QString m_graphizPath;
    QString m_cachePath;

    QString m_customJavaPath;
    QString m_customPlantUmlPath;
    QString m_customGraphizPath;
    QString m_customCachePath;

    bool m_hasValidPaths;

    QProcess *m_process;
    QMap<ImageFormat, QString> m_imageFormatNames;
    ImageFormat m_currentImageFormat;
    QTimer *m_autoRefreshTimer;
    bool m_needsRefresh;

    QTextEdit *m_editor;
    PreviewWidget *m_imageWidget;

    QToolBox *m_assistantToolBox;
    QLabel *m_assistantPreviewNotes;
    QTextEdit *m_assistantCodePreview;

    QToolBar *m_mainToolBar;

    QMenu *m_fileMenu;
    QAction *m_newDocumentAction;
    QAction *m_openDocumentAction;
    QAction *m_saveDocumentAction;
    QAction *m_saveAsDocumentAction;
    QAction *m_exportImageAction;
    QAction *m_exportAsImageAction;
    QAction *m_quitAction;

    QMenu *m_editMenu;
    QAction *m_undoAction;
    QAction *m_redoAction;
    QAction *m_refreshAction;

    QMenu *m_settingsMenu;
    QAction *m_showAssistantDockAction;
    QAction *m_showAssistantInfoDockAction;
    QAction *m_showEditorDockAction;
    QAction *m_showMainToolbarAction;
    QAction *m_showStatusBarAction;
    QAction *m_pngPreviewAction;
    QAction *m_svgPreviewAction;
    QAction *m_autoRefreshAction;
    QAction *m_autoSaveImageAction;
    QAction *m_preferencesAction;

    QMenu *m_helpMenu;
    QAction *m_aboutAction;
    QAction *m_aboutQtAction;

    QSignalMapper* m_assistantPreviewSignalMapper;
    QSignalMapper* m_assistantInsertSignalMapper;

    FileCache* m_cache;
    RecentDocuments* m_recentDocuments;
};

#endif // MAINWINDOW_H
