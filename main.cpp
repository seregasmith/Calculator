#include <QCoreApplication>

#include <QtCore>
#include <iostream>
#include <string>

#include "helper.h"
#include "parser.h"
#include "expression.h"

class Task : public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0) : QObject(parent) {}

public slots:
    void run()
    {
        // Do processing here

        std::cout << "\n";
        helper::printHelp();
        Parser::test();

//        std::string input = "1+(26-98)/15+77<28";
//        Parser * parser = new Parser(input);
//        Expression * expressionTree = parser->parse();
//        long result = expressionTree->calculate();

//        std::cout << "RESULT: "<< result <<"\n";
        emit finished();
    }

signals:
    void finished();
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Task parented to the application so that it
    // will be deleted by the application.
    Task *task = new Task(&a);

    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, task, SLOT(run()));

    return a.exec();
}
