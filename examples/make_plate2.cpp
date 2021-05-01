//-----------------------
//program for make nodes and elems file
//-----------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std ;

class Cood{
    //data
    public:
        double x ;
        double y ;
};

int main(void){
    double a = 3 ; //half diameter of circular.
    double w = 10 ; //half of width of plane - a
    double h = 15 ; //half of height of plane - a
    double fswratio = 1 ; //is the ratio of width of part 1 and part 2. namely p1/p2=ratio
    int n = 6 ; //split number for part 1.
    vector< Cood >  Coods ; //coordinations of nodes.


    //pre process. measure lengths etc...
    if(w > h){
        cout << "must h be larger than w";
        return -1 ;
    }

    double len_1 = w/(1+1/fswratio) ;
    double w_2 = w - len_1 ;
    double h_2 = h - len_1 ;
    double w_3 = w - (len_1 + a)*cos(1/(3*M_PI)) ;
    double h_3 = h - (len_1 + a)*cos(1/(3*M_PI)) ;
    double w_4 = w - w_2 ;
    double h_4 = h - h_2 ;

    //part1
    double x,y ;
    x = 0 ;
    y = 0 ;
    int count = 1 ;
    int div = n ; //バウムクーヘン層方向分割数．もっと考える必要あり．
    for (int i = 0; i < div+2; i++) //r方向分割数分(未定)だけ行う
    {
        double len_i = a + i*len_1/(div +1) ;
        for (int j = 0; j < n+1; j++) //週方向
        {
            //反時計回りに
            x = len_i * cos(double(j)/(double(n)*2)*M_PI) ;
            y = len_i * sin(double(j)/(double(n)*2)*M_PI) ;
            cout << count << "  " << x << "  " << y << "\n" ;
            count ++;
        }
    }

    //part2.1
    for (int i = 0; i < 5; i++) {
        y = 10 + i*2 ;
        x =0 ;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;

        x = 2.07055 ;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;

        x=4 ;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;
    }

    //part2.2
    for (int i = 0; i < 2; i++) {
        x = 10 + i*3 ;
        y = 0 ;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;

        y = 2.07055 ;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;

        y=4 ;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;
    }

    //part3
    x = 6.9282 ;
    y = 5.65685 ;
    cout << count << "  " << x << "  " << y << "\n" ;
    count++ ;

    for (int i = 0; i < 2; i++) {
        x = 10 + i*3 ;
        y = 5.65685;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;
    }

    x = 5.65685 ;
    y = 6.9282 ;
    cout << count << "  " << x << "  " << y << "\n" ;
    count++ ;

    x = 6.9282 ;
    y = 6.9282 ;
    cout << count << "  " << x << "  " << y << "\n" ;
    count++ ;

    for (int i = 0; i < 2; i++) {
        x = 10 + i*3 ;
        y = 6.9282;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;
    }

    for (int i = 0; i < 5; i++) {
        x = 5.65685;
        y = 10 + i*2 ;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;

        x = 6.9282;
        cout << count << "  " << x << "  " << y << "\n" ;
        count++ ;

        for (int i = 0; i < 2; i++) {
            x = 10 + i*3 ;
            cout << count << "  " << x << "  " << y << "\n" ;
            count++ ;
        }
    }

    //element
    //part1
    int b = 0 ;
    int c = 0 ;
    int d = 0 ;
    count = 1 ;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            b=1+2*j+7*i; c=8+2*j+7*i ; d=9+2*j+7*i;
            cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
            count++ ;
            b=9+2*j+7*i; c=2+2*j+7*i ; d=1+2*j+7*i;
            cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
            count++ ;
            b=9+2*j+7*i; c=10+2*j+7*i ; d=3+2*j+7*i;
            cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
            count++ ;
            b=2+2*j+7*i; c=9+2*j+7*i ; d=3+2*j+7*i;
            cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
            count++ ;
        }
    }
    //part2 1
    b=58 ; c=57; d=56;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=58 ; c=56; d=55;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=58 ; c=55; d=54;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=59 ; c=58; d=54;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    for (int i = 0; i < 5; i++) {
        b=60+2*i ; c=57+2*i; d=61+2*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
        b=57+2*i ; c=58+2*i; d=61+2*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
        b=61+2*i ; c=58+2*i; d=59+2*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
        b=62+2*i ; c=61+2*i; d=59+2*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
    }

    //part2 2
    b=52 ; c=51; d=73;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=74 ; c=52; d=73;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=73 ; c=51; d=50;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=73 ; c=50; d=72;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=74 ; c=73; d=76;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=77 ; c=51; d=76;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=76 ; c=73; d=72;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=76 ; c=72; d=75;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;

    //part3
    b=78 ; c=53; d=52;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=81 ; c=54; d=53;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=81 ; c=53; d=78;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=82 ; c=81; d=78;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;

    b=82 ; c=78; d=83;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=83 ; c=78; d=79;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=83 ; c=79; d=80;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=84 ; c=83; d=80;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;

    for (int i = 0; i < 5; i++) {
        b=85+4*i ; c=81+4*i; d=82+4*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
        b=86+4*i ; c=85+4*i; d=82+4*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
        b=87+4*i ; c=86+4*i; d=82+4*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
        b=87+4*i ; c=82+4*i; d=83+4*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
        b=87+4*i ; c=83+4*i; d=84+4*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
        b=88+4*i ; c=87+4*i; d=84+4*i;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
    }

    //boundary of part 2 and 3
    b=78 ; c=52; d=79;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=79 ; c=52; d=74;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=79 ; c=74; d=77;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;
    b=80 ; c=79; d=77;
    cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
    count++ ;

    for (int i = 0; i < 5; i++) {
        b=59+i*3 ; c=54+i*3; d=85+i*4;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
        b=85+i*4 ; c=54+i*3; d=81+i*4;
        cout << count << "  " << b << "  " << c << "  " << d << "\n" ;
        count++ ;
    }

    return 0 ;
}
