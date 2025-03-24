#pragma once

namespace CMB {
    union Color {
        uint32_t RGB888;
        struct {
            byte b;
            byte g;
            byte r;
        } RGB;
    };

    class Base_RGB {
        public:
        void tick() {
            if(color.RGB888 != _color.RGB888) {
                _color = color;
                setRGB(_color);
            }
        }

        virtual void setR(byte val) = 0;
        virtual void setG(byte val) = 0;
        virtual void setB(byte val) = 0;
        void setRGB(byte r, byte g, byte b) {setR(r);setG(g);setB(b);}
        void setRGB(CMB::Color c) {setRGB(c.RGB.r, c.RGB.g, c.RGB.b);}

        CMB::Color color {0};

        protected:
        CMB::Color _color {0};
    };
}    