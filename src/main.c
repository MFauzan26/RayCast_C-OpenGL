#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define P2 M_PI/2    //  90 derajat
#define P3 3*M_PI/2  // 270 derajat
#define DR 0.0174533 // 1 derajat di radian

float frame1, frame2, fps;

float FixAng(float a)
{ 
    if (a<0)           {a+=2*M_PI;}  // jika angle di bawah 0 maka akan menjadi 360 derajat
    if (a>(2*M_PI)-DR) {a-=2*M_PI;}  // jika angle di atas 360 maka akan menjadi 0 derajat
    return a;
}

// -- texture --
int bit_texture[] =  // ukuran 32 x 32
{
    // tembok bata
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2,
    2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2,
    1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0,
    0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0,
    0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2,
    2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2,
    1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0,
    0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0, 0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0,
    0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,2,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    //Checkerboard
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
    1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
};

// -- fungsi map --
int mapX =  8;  // ukuran map X per-blok
int mapY =  8;  // ukuran map Y per-blok
int mapS = 64;  // ukuran 1 blok 
// array map
int map_dinding[] =  // ukuran 8 x 8 
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 1, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 1, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1
};

int map_lantai[] =  // ukuran 8 x 8 
{
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
};


void render_map2D()
{
    int x, y, xo, yo;
    for (y=0; y<mapY; y++)
    {
        for (x=0; x<mapX; x++)
        {
            if (map_dinding[y*mapX+x] != 0) {glColor3f(1, 1, 1);}  // jika map index bukan 0 maka warnanya putih
            else {glColor3f(0, 0, 0);}                             // jika map index 0 maka warnanya hitam
            xo=x*mapS; yo=y*mapS;
            // gambar kota untuk map
            glBegin(GL_QUADS);
            glVertex2i(0+xo+1   ,    0+yo+1);
            glVertex2i(0+xo+1   , yo+mapS-1);
            glVertex2i(xo+mapS-1, yo+mapS-1);
            glVertex2i(xo+mapS-1,    0+yo+1);
            glEnd();
        }
    }
}

// -- fungsi pemain --
float px, py, pdx, pdy, pa;  // posisi pemain
void render_pemain()
{
    // pemain
    glColor3f(1, 1, 0);
    glPointSize(8);/*
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();
    // garis
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px+pdx*5, py+pdy*5);
    glEnd();*/
}

// -- dinding dan lantai --
void render_flocel()
{
    // langit
    glColor3f( 0, 0.3, 0.7);
    glBegin(GL_QUADS);
    glVertex2i(0,     0);
    glVertex2i(480,   0);
    glVertex2i(480, 320);
    glVertex2i(0,   320);
    glEnd();
} 

// -- fungsi ray cast 2D --
int dist(float ax, float ay, float bx, float by, float ang)
{
    return ( sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay)) );
}

void render_ray2D()
{
    int   r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, disT;
    ra = pa-DR*30; 
    if(ra<0)      {ra+=2*M_PI;}  // jika angle di bawah 0 maka akan menjadi 360 derajat
    if(ra>2*M_PI) {ra-=2*M_PI;}  // jika angle di atas 360 maka akan menjadi 0 derajat
    // lantai 1
    for (r=0; r<61; r++)
    {
        //////////////////////////
        // cek garis horizontal //
        //////////////////////////
        dof = 0;
        float hx   = px;
        float hy   = py;
        float disH = 1000000;
        float aTan = -1/tan(ra);
        if (ra < M_PI)  // lihat atas (angle di bawah 180 derajat)
        {
            ry=(((int)py>>6)<<6)+64; rx=(py-ry)*aTan+px;
            yo=64; xo=-yo*aTan;
        }
        if (ra > M_PI)  // lihat bawah (angle di atas 180 derajat)
        {
            ry=(((int)py>>6)<<6)-0.0001; rx=(py-ry)*aTan+px;
            yo=-64; xo =-yo*aTan;
        }
        if (ra == 0 || ra == M_PI)  // lihat lurus ke samping
        {
            rx=px; ry=py;
            dof = 8; 
        } 
        while(dof<8)  // loop sampai ketemu tembok
        {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if (mp>0 && mp<mapX*mapY && map_dinding[mp]==1)   // jika menabrak dinding maka berhenti
            {
                hx=rx; hy=ry;
                disH = dist(px, py, hx, hy, ra);
                dof  = 8;
            }
            else {rx+=xo; ry+=yo; dof+=1;}  // jika tidak menabrak dinding maka lanjut
        }  
        
        ////////////////////////
        // cek garis vertikal //
        ////////////////////////
        dof=0;
        float vx   = px;
        float vy   = py;
        float disV = 1000000;
        float nTan = -tan(ra);
        if (ra < P2 || ra > P3)  // lihat kanan (angle di bawah 90 dan di atas 270 derajat)
        {
            rx=(((int)px>>6)<<6)+64; ry=(px-rx)*nTan+py;
            xo=64; yo=-xo*nTan;
        }
        if (ra > P2 && ra < P3)  // lihat kiri (angle di atas 90 dan di bawah 270 derajat)
        {
            rx=(((int)px>>6)<<6)-0.0001; ry=(px-rx)*nTan+py;
            xo=-64; yo =-xo*nTan;
        }
        if (ra == 0 || ra == M_PI)  // lihat lurus ke atas atau bawah
        {
            rx=px; rx=px;
            dof = 8; 
        } 
        while(dof<8)  // loop sampai ketemu tembok
        {
            mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;
            if (mp>0 && mp<mapX*mapY && map_dinding[mp]==1)   // jika menabrak dinding maka berhenti
            {
                vx=rx; vy=ry;
                disV = dist(px, py, vx, vy, ra);
                dof  = 8;
            } 
            else {rx+=xo; ry+=yo; dof+=1;}  // jika tidak menabrak dinding maka lanjut
        }
        float shade;
        // memilih garis terdekat
        if (disV < disH) {rx=vx; ry=vy; disT=disV; shade=0.5;}  // jika garis vertikal lebih dekat
        if (disV > disH) {rx=hx; ry=hy; disT=disH; shade=1.0;}  // jika garis horizontal lebih dekat
        // render ray cast
        /*glColor3f(0, 0, 1);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();*/
        // -- gambar dinding 3D --
        float ca = pa-ra; if (ca<0) {ca+=2*M_PI;} if (ca>2*M_PI) {ca-=2*M_PI;} 
        disT=disT*cos(ca);                // membetulkan efek "fish eye"
        float lineH   = (mapS*320/disT);  // menetapkan ukuran maksimal dinding (320 pixel)
        float ty_step = 32.0/(float)lineH;
        float ty_off  = 0;
        if (lineH>320) {ty_off=(lineH-320)/2.0; lineH=320;}
        float lineO = 160-lineH/2;  // menetapkan posisi dinding
        // render setiap dinding
        int   y;
        float ty = ty_off*ty_step;
        float tx;
        if(shade==1)  // memberi texture ketika dindig menghadap utara dan selatan
        {
            tx=(int)(rx/2.0)%32; 
            if(ra>M_PI) {tx=31-tx;};
        }
        else  // memberi texture ketika dindig menghadap timur dan barat  
        {
            tx=(int)(ry/2.0)%32; 
            if(ra>P2/2 && ra<P3) {tx=31-tx;};
        }
        for (y=0; y<lineH; y++)
        {
            float red, green, blue;
            if (bit_texture[(int)(ty)*32+(int)(tx)] == 0) {red=0  *shade; green=0  *shade; blue=0  *shade;}
            if (bit_texture[(int)(ty)*32+(int)(tx)] == 1) {red=0.5*shade; green=0.5*shade; blue=0.5*shade;}
            if (bit_texture[(int)(ty)*32+(int)(tx)] == 2) {red=0.9*shade; green=0.9*shade; blue=0.9*shade;}
            glColor3f(red, green, blue);
            glLineWidth(8);
            glBegin(GL_POINTS);
            glVertex2i(r*8, y+lineO);
            glEnd();
            ty += ty_step;
        }
        // -- gambar lantai --
        for(y=lineO+lineH; y<320; y++)
        {
            float dy    = y-(320/2.0);
            float deg   = ra;
            float raFix = cos(FixAng(pa-ra));
            tx = px / 2 + cos(deg) *  158 * 32 / dy / raFix;
            ty = py / 2 + sin(deg) *  158 * 32 / dy / raFix;
            int   mp = map_lantai[(int)(ty/32.0)*mapX+(int)(tx/32.0)]*32*32;
            float c  = bit_texture[((int)(ty)&31)*32 + ((int)(tx)&31)+mp]*0.7;
            glColor3f(c*0, c*0.5, c*0);
            glPointSize(8);
            glBegin(GL_POINTS);
            glVertex2i(r*8, y);
            glEnd();
        }
        // menambahkan derajat di setiap raycast
        ra += DR;
        if (ra<0)      {ra+=2*M_PI;}  // jika angle di bawah 0 maka akan menjadi 360 derajat
        if (ra>2*M_PI) {ra-=2*M_PI;}  // jika angle di atas 360 maka akan menjadi 0 derajat
    }
}

// -- fungsi tampilan --
void tampilan()
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // panggil fungi untuk dirender ///////
    //render_map2D(); // fungsi map
    render_flocel();  // fungsi langit dan lantai
    render_ray2D();   // fungsi ray2D 
    render_pemain();  // fungsi player
    ///////////////////////////////////////
    glutSwapBuffers();
}

// -- fungsi input --
void tombol(unsigned char key, int x, int y)
{
    if(key == 'a') {pa-=0.1; if(pa<     0){pa+=2*M_PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;}  // kiri
    if(key == 'd') {pa+=0.1; if(pa>2*M_PI){pa-=2*M_PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;}  // kanan
    if(key == 'w') {px+=pdx; py+=pdy;}                                                  // maju
    if(key == 's') {px-=pdx; py-=pdy;}                                                  // mundur
    glutPostRedisplay(); 
}

// -- fungsi update --
void init()
{
    glClearColor(0, 0, 0, 0);      // warna layar (hitam)
    gluOrtho2D(0, 480, 320, 00);   // ukuran layar
    px=300; py=300;                // menetapkan posisi X dan Y pemain
    pdx=cos(pa)*5; pdy=sin(pa)*5;  // posisi delta X dan Y pemain              
}

// -- fungsi utama --
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(480, 320);          // ukuran layar
    glutInitWindowPosition(400, 200);      // posisi layar muncul
    glutCreateWindow("Raycast - Fauzan");  // nama window
    init();                                // panggil fungsi init (update)
    glutDisplayFunc(tampilan);             // fungsi tampilan
    glutKeyboardFunc(tombol);              // fungsi input keyboar
    glutMainLoop();                        // loop layar agar tidak keluar
}
