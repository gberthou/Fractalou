#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED

class Colors 
{
    public:
        static void HsvToRgb(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char h, unsigned char s, unsigned char v);
    
        Colors();
        virtual ~Colors();
        
    protected:
};


#endif // COLORS_H_INCLUDED
