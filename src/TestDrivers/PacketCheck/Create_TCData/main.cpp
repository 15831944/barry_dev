#include <qapplication.h>
#include "mydialog.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    MyDialog w;
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
