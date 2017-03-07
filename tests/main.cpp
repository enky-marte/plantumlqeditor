#include <QString>
#include <QDate>
#include <QGuiApplication>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

void PrintTo(const QString& string, ::std::ostream* os) {
    *os<< "\"" << string.toStdString() << "\"";
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);

    QGuiApplication gui(argc, argv);
    Q_UNUSED(gui);

    return RUN_ALL_TESTS();
}
