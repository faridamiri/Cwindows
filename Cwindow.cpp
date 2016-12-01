/* 
 * File:   main.cpp
 * Author: Farid Amiri compaq
 *
 * Created on April 25, 2012, 8:02 PM
 */

#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;
#endif /* __PROGTEST__ */

class CControl {
public:

    CControl(int ID) {
        this->ID = ID;
    }
    virtual ~CControl(){
        ID=0;
    }




    virtual std::ostream& print(std::ostream& stm) const = 0;
    virtual CControl * Clone()const = 0;
    virtual void SetInWindow(int pre_x, int pre_y, int pre_w, int pre_h, int bx, int by, int bw, int bh) = 0;

    int getID() {
        return (this->ID);
    }
   

private:
    int ID;
};
bool checkLine, checkSpace;

inline ostream& operator<<(ostream& os, const CControl& s) {
    if (&s) return s.print(os);
    else return os;
}

////////////////////////////////////////////////CButton//////////////////////

class CButton : public CControl {
public:

    CButton(int ID, double x, double y, double w, double h, string text) : CControl(ID) {
        this->ID = ID;
        this->x = (x >= 0 && x <= 1) ? x : 0;
        this->y = (y >= 0 && y <= 1) ? y : 0;
        this->w = (w >= 0 && w <= 1) ? w : 0;
        this->h = (h >= 0 && h <= 1) ? h : 0;
        this->text = text;
    }

    ~CButton() {
        text.clear();
        this->x = 0;
        this->y = 0;
        this->w = 0;
        this->h = 0;

    }

    std::ostream& print(std::ostream& os) const {
        os << "[" << ID << "] Button \"" << text << "\" (" << (int) x << "," << (int) y << "," << (int) w << "," << (int) h << ")";
        os << endl;
        return os;
    }

    CControl * Clone()const {
        return ( new CButton(*this));
    }

    void SetInWindow(int pre_x, int pre_y, int pre_w, int pre_h, int bx, int by, int bw, int bh) {
        if (pre_w == 0 || pre_h == 0)return;
        h = h * bh / pre_h;
        w = w * bw / pre_w;
        x = bx + (x - pre_x) * bw / pre_w;
        y = by + (y - pre_y) * bh / pre_h;

    }

 
protected:
    int ID;
    double x;
    double y;
    double w;
    double h;
    string text;

};


///////////////////////////////////////////////
////////////////////////////////////////////////CLabel//////////////////////

class CLabel : public CControl {
public:

    CLabel(int ID, double x, double y, double w, double h, string text) : CControl(ID) {
        this->ID = ID;
        this->x = (x >= 0 && x <= 1) ? x : 0;
        this->y = (y >= 0 && y <= 1) ? y : 0;
        this->w = (w >= 0 && w <= 1) ? w : 0;
        this->h = (h >= 0 && h <= 1) ? h : 0;
        this->text = text;
    }

    ~CLabel() {
        text.clear();
        this->x = 0;
        this->y = 0;
        this->w = 0;
        this->h = 0;

    }

    std::ostream& print(std::ostream& os) const {
        os << "[" << ID << "] Label \"" << text << "\" (" << (int) x << "," << (int) y << "," << (int) w << "," << (int) h << ")";
        os << endl;
        return os;
    }

    CControl * Clone()const {
        return ( new CLabel(*this));
    }

    void SetInWindow(int pre_x, int pre_y, int pre_w, int pre_h, int bx, int by, int bw, int bh) {
        if (pre_w == 0 || pre_h == 0)return;
        h = h * bh / pre_h;
        w = w * bw / pre_w;
        x = bx + (x - pre_x) * bw / pre_w;
        y = by + (y - pre_y) * bh / pre_h;
    }

 
protected:
    int ID;
    double x;
    double y;
    double w;
    double h;
    string text;
};



////////////////////////////////////////////////Cinput//////////////////////

class CInput : public CControl {
public:

    CInput(int ID, double x, double y, double w, double h, string text) : CControl(ID) {
        this->ID = ID;
        this->x = (x >= 0 && x <= 1) ? x : 0;
        this->y = (y >= 0 && y <= 1) ? y : 0;
        this->w = (w >= 0 && w <= 1) ? w : 0;
        this->h = (h >= 0 && h <= 1) ? h : 0;
        this->text = text;

    }

    std::ostream& print(std::ostream& os) const {

        os << "[" << ID << "] Input \"" << text << "\" (" << (int) x << "," << (int) y << "," << (int) w << "," << (int) h << ")";
        os << endl;
        return os;
    }

    ~CInput() {
        text.clear();
        this->x = 0;
        this->y = 0;
        this->w = 0;
        this->h = 0;
    }

    CControl * Clone()const {
        return ( new CInput(*this));
    }

    void SetValue(string x) {
        this->text = x;
    }

    string GetValue() {
        return this->text;
    }

    void SetInWindow(int pre_x, int pre_y, int pre_w, int pre_h, int bx, int by, int bw, int bh) {
        if (pre_w == 0 || pre_h == 0)return;
        h = h * bh / pre_h;
        w = w * bw / pre_w;
        x = bx + (x - pre_x) * bw / pre_w;
        y = by + (y - pre_y) * bh / pre_h;

    }

   


protected:
    int ID;
    double x;
    double y;
    double w;
    double h;
    string text;

};


////////////////////////////////////////////////Combo//////////////////////

class CComboBox : public CControl {
public:

    CComboBox(int ID, double x, double y, double w, double h) : CControl(ID) {

        this->ID = ID;
        this->x = (x >= 0 && x <= 1) ? x : 0;
        this->y = (y >= 0 && y <= 1) ? y : 0;
        this->w = (w >= 0 && w <= 1) ? w : 0;
        this->h = (h >= 0 && h <= 1) ? h : 0;
        this->numMember = 0;
        this->selectItem = 0;
        this->text = new string[50];

    }

    ~CComboBox() {
        delete [] text;

        this->x = 0;
        this->y = 0;
        this->w = 0;
        this->h = 0;
        this->numMember = 0;
        this->selectItem = 0;
       

    }

    CComboBox & Add(string x) {
        text[numMember] = x;
        numMember++;
        return * this;
    }

    ostream& print(ostream& os) const {
        os << "[" << ID << "] ComboBox " << "(" << (int) x << "," << (int) y << "," << (int) w << "," << (int) h << ")";
        for (int i = 0; i < numMember; i++) {
            os << endl;
            if (checkLine)os << "|";
            if (checkSpace)os << "  ";
            if (!checkLine && checkSpace)os << " ";
            os << "+-";
            if (i == selectItem) os << ">";
            else os << " ";
            os << text[i];
            if (i == selectItem) os << "<";
        }
        os << endl;
        return os;
    }

    CControl * Clone()const {
        CComboBox *  X=new CComboBox(*this);
        X->text=new string[50];         
        for (int i = 0; i < numMember; i++) {
            
            X->text[i]=text[i];


        }

        return ( X );
    }

    void SetSelected(int item) {
        if (item < numMember)selectItem = item;
    }

    void SetInWindow(int pre_x, int pre_y, int pre_w, int pre_h, int bx, int by, int bw, int bh) {
        if (pre_w == 0 || pre_h == 0)return;
        h = h * bh / pre_h;
        w = w * bw / pre_w;
        x = bx + (x - pre_x) * bw / pre_w;
        y = by + (y - pre_y) * bh / pre_h;

    }

    




protected:
    int ID;
    double x;
    double y;
    double w;
    double h;
    string * text;
    int numMember;
    int selectItem;

};



/////////////////////////////CWindow////////////////////////////////////

class CWindow {
public:

    CWindow(string title, int x, int y, int w, int h);
    CWindow();
    void SetPosition(int x, int y, int w, int h);
    CWindow & Add(const CControl&);
    CWindow & Insert(const CControl& control);
    CWindow(const CWindow & rOperand);
    CControl * Search(int identitiy);
    ~CWindow();

    CWindow & operator =(const CWindow& X) {
        title = X.title;
        x = X.x;
        y = X.y;
        w = X.w;
        h = X.h;
        Root = NULL;
        Node * rnode;
        const CControl * tmpCtrl;
        rnode = X.Root;

        while (rnode) {
            tmpCtrl = rnode->control;

            Insert(*tmpCtrl);
            rnode = rnode->NextControl;

        }



        return * this;
    }

    friend ostream & operator <<(ostream & os, const CWindow & x) {
        checkLine = false;
        checkSpace = false;
        if (!(&x))return os;
        os << "Window \"" << x.title << "\" (";
        os << x.x << ",";
        os << x.y << ",";
        os << x.w << ",";
        os << x.h;
        os << ")";
        const CControl * tmpControl;
        Node * tmpNode;
        tmpNode = x.Root;
        os << endl;
        while (tmpNode) {

            tmpControl = tmpNode->control;
            if (tmpNode->NextControl)checkLine = true;
            checkSpace = true;

            os << "+- " << *tmpControl;
            checkLine = false;
            checkSpace = false;
            tmpNode = tmpNode->NextControl;

        }
        return os;
    }

    struct Node {
        const CControl * control;
        Node* NextControl; //pointer to other Control in this node 
    };
    Node* Root;
protected:
    string title;
    int x;
    int y;
    int w;
    int h;
};

CWindow & CWindow::Insert(const CControl& control) {

    Node * node;
    node = new Node;

    node->control = control.Clone();
    node->NextControl = NULL;
    if (!Root) {
        Root = node;
    } else {
        Node * tmp;
        tmp = Root;
        while (tmp->NextControl)tmp = tmp->NextControl;
        tmp->NextControl = node;

    }

    return * this;
}

CWindow & CWindow::Add(const CControl& control) {

    Node * node;
    node = new Node;

    node->control = control.Clone();
    CControl * tmpCtrl;
    tmpCtrl = (CControl *) node->control;
    tmpCtrl->SetInWindow(0, 0, 1, 1, x, y, w, h);
    node->NextControl = NULL;
    if (!Root) {
        Root = node;
    } else {
        Node * tmp;
        tmp = Root;
        while (tmp->NextControl)tmp = tmp->NextControl;
        tmp->NextControl = node;

    }

    return * this;
}

void CWindow::SetPosition(int nx, int ny, int nw, int nh) {
    Node * node;
    CControl * tmpCtrl;
    node = Root;

    while (node) {
        tmpCtrl = (CControl *) node->control;
        tmpCtrl->SetInWindow(x, y, w, h, nx, ny, nw, nh);
        node = node->NextControl;

    }

    x = nx;
    y = ny;
    w = nw;
    h = nh;


}

CWindow::CWindow(string title, int x, int y, int w, int h) {
    this->title = title;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    Root = NULL;
}

CWindow::CWindow() {
    this->title = "";
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    Root = NULL;
}

CWindow::CWindow(const CWindow & rOperand) {



    title = rOperand.title;
    x = rOperand.x;
    y = rOperand.y;
    w = rOperand.w;
    h = rOperand.h;
    Root = NULL;
    Node * rnode;
    const CControl * tmpCtrl;
    rnode = rOperand.Root;

    while (rnode) {
        tmpCtrl = rnode->control;

        Insert(*tmpCtrl);
        rnode = rnode->NextControl;

    }

}

CControl * CWindow::Search(int identitiy) {
    Node * node;
    CControl * tmpCtrl;
    node = Root;

    while (node) {
        tmpCtrl = (CControl *) node->control;
        if (identitiy == tmpCtrl->getID())
            return tmpCtrl;

        node = node->NextControl;

    }
    return NULL;


}

CWindow::~CWindow() {



    Node * node;
    Node * next;
    CControl * tmpCtrl;
    node = Root;

    while (node) {
        next = node->NextControl; 
        tmpCtrl = (CControl *) node->control;
        delete tmpCtrl;
        
        node->NextControl = NULL;
        delete node;
        node = next;
        Root = next;

    }
    checkLine = false;
    checkSpace = false;
    title.clear();
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    tmpCtrl=NULL;
    node=NULL;
    next=NULL;

    delete  Root;


}




    /*
     * 
     */
#ifndef __PROGTEST__

    int main(int argc, char** argv) {
        CWindow a("Sample window", 10, 10, 600, 480);
         a . Add(CButton(1, 0.1, 0.8, 0.3, 0.1, "Ok")) . Add(CButton(2, 0.6, 0.8, 0.3, 0.1, "Cancel"));
         a . Add(CLabel(10, 0.1, 0.1, 0.2, 0.1, "Username:"));
         a . Add(CInput(11, 0.4, 0.1, 0.5, 0.1, "chucknorris"));
          a . Add(CComboBox(20, 0.1, 0.3, 0.8, 0.1) . Add("Karate") . Add("Judo") . Add("Box") . Add("Progtest"));
          a . Add(CInput(51, 0.4, 0.1, 0.5, 0.1, "chucknorris"));
        a . Add(CComboBox(50, 0.1, 0.3, 0.8, 0.1) . Add("Karate") . Add("Judo") . Add("Box") . Add("Progtest"));
       // a . Add(CInput(52, 0.4, 0.1, 0.5, .42333332233, "chucknorris"));
        cout << a;
        /*
        Window "Sample window" (10,10,600,480)
        +- [1] Button "Ok" (70,394,180,48)
        +- [2] Button "Cancel" (370,394,180,48)
        +- [10] Label "Username:" (70,58,120,48)
        +- [11] Input "chucknorris" (250,58,300,48)
        +- [20] ComboBox (70,154,480,48)
           +->Karate<
           +- Judo
           +- Box
           +- Progtest
         */
        CWindow b;
        b = a;
          CControl * ctl = b . Search(50);
           cout << *ctl;
        CComboBox * cb = dynamic_cast<CComboBox *> (b . Search(50));
        CComboBox * ca = dynamic_cast<CComboBox *> (a . Search(50));
        cb->Add("joke");
        ca->Add("Legratce");
        cout<<a;
        cout << *cb;
        cout << *ca;

       // b.~CWindow();
         
        return 0;
        /*
        [20] ComboBox (70,154,480,48)
        +->Karate<
        +- Judo
        +- Box
        +- Progtest
         */
        //  CComboBox * cb = dynamic_cast<CComboBox *> (b . Search(20));
        //  cb -> SetSelected(3);
        //  CInput * il = dynamic_cast<CInput *> (b . Search(11));
        //   cout << *il;
        //   il -> SetValue("chucknorris@fit.cvut.cz");
        //   b . Add(CComboBox(21, 0.1, 0.5, 0.8, 0.1) . Add("PA2") . Add("OSY") . Add("Both"));
        //   b . Add(CInput(11, 0.4, 0.1, 0.5, 0.1, "chucknorris"));
        //   b . Add(CComboBox(22, 0.1, 0.5, 0.8, 0.1) . Add("PA2") . Add("OSY") . Add("Both"));
        //   cout << b;
        /*
        Window "Sample window" (10,10,600,480)
        +- [1] Button "Ok" (70,394,180,48)
        +- [2] Button "Cancel" (370,394,180,48)
        +- [10] Label "Username:" (70,58,120,48)
        +- [11] Input "chucknorris@apimvc.com" (250,58,300,48)
        +- [20] ComboBox (70,154,480,48)
        |  +- Karate
        |  +- Judo
        |  +- Box
        |  +->Progtest<
        +- [21] ComboBox (70,250,480,48)
           +->PA2<
           +- OSY
           +- Both
         */
        //  b . SetPosition(20, 30, 640, 520);
        //  cout << b;
        /*
        Window "Sample window" (20,30,640,520)
        +- [1] Button "Ok" (84,446,192,52)
        +- [2] Button "Cancel" (404,446,192,52)
        +- [10] Label "Username:" (84,82,128,52)
        +- [11] Input "chucknorris@fit.cvut.cz" (276,82,320,52)
        +- [20] ComboBox (84,186,512,52)
        |  +- Karate
        |  +- Judo
        |  +- Box
        |  +->Progtest<
        +- [21] ComboBox (84,290,512,52)
           +->PA2<
           +- OSY
           +- Both
         */
        //  return 0;
    }
#endif /* __PROGTEST__ */