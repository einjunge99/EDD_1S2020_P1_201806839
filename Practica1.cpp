#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

using namespace std;

void gotoxy(int x,int y){
    HANDLE hCon;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hCon,dwPos);
}
void hideCursor(){
    HANDLE hCon;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize=2;
    cci.bVisible= FALSE;
    SetConsoleCursorInfo(hCon,&cci);
}

class circularNode{
public:
    string data;
    circularNode *next;
    circularNode(){}
    circularNode(string data){
        this->data=data;
        next=NULL;
    }
};
class circularList{
private:
    circularNode *header;
    int size;
public:
    circularList(){
        header=NULL;
        size=0;
    }
    void prepend(circularNode *node){
        if(header==NULL){
            header=node;
            node->next=header;
        }
        else{
            circularNode *temp=header;
            while(temp->next!=header){
                temp=temp->next;
            }
            node->next=header;
            header=node;
            temp->next=header;
        }
        size++;
    }
    bool search(string param){
        int cont=0;
        bool found=false;
        circularNode *temp=header;
        gotoxy(4,1);
        cout<<"x(Reporte archivos)";
        if(size!=0){
            while(cont<size){
                if(temp->data==param){
                    found=true;
                }
                temp=temp->next;
                cont++;
            }
        }
        return found;
    }
    void showData(){
        int cont=0;
        int y=4;
        circularNode *temp=header;
        gotoxy(4,1);
        cout<<"x(Reporte archivos)";
        if(size!=0){
            while(cont<size){
                gotoxy(3,y);
                cout<<to_string(cont+1)+".  C:\\Users\\Isaac Maldonado\\Desktop\\"+temp->data;
                y++;
                gotoxy(3,y);
                cout<<"    "+temp->data;
                temp=temp->next;
                y++;
                cont++;
            }
        }

    }
    string fourthReport() {
        string info = "";
        int cont = 0;
        circularNode *temp = header;
        info += "rankdir=LR; node [ shape=square ];  ";
        if (size!=0) {
        while (cont<size) {
            info += "n_" + to_string(cont) + "[label=<" + temp->data +" <br align=\"left\"/>C:\\Users\\Isaac Maldonado\\Desktop\\" + temp->data +" <br align=\"left\"/>   >];";
            temp = temp->next;
            cont++;
        }
        if (cont != 0) {
            int i=0;
            for (int i = 0; i < cont - 1; i++) {
                info += "n_" + to_string(i) + "->";
            }
            info += "n_" + to_string(i) + "-> n_" + to_string(i);
        }
    }
        return info;
    }
};

class Log{
public:
    string search="";
    string update="";
    bool status;
    char letra=' ';
    int position=0;
    string type;
    string list;
    Log(){}
    Log(string search, string update, bool status,string list){
        this->search=search;
        this->update=update;
        this->status=status;
        this->list=list;
    }
    Log(char letra, int position, bool status){
        this->status=status;
        this->letra=letra;
        this->position=position;
    }
};
class stackNode{
public:
    stackNode *next;
    Log *data;
    stackNode(Log *data){
        this->data=data;
        next=NULL;
    }
};
class stack{
private:
    stackNode *top;
    int cont=0;
public :

    stack(){
    top=NULL;
}
void cleanStack(){
    top=NULL;
    cont=0;
}
void push(Log *log){

    stackNode *node=new stackNode(log);
    if(top==NULL){
        top=node;
        cont++;
    }
    else{
        node->next=top;
        top=node;
        cont++;
    }
}
Log *pop(){
    if(top!=NULL){
        Log *tempData=top->data;
        stackNode *temp=top;
        top=top->next;
        cont--;
        delete temp;
        return tempData;
    }
   }
   int stackSize(){
       return cont;
}
string secondReport(string param){
        string info="";
        int cont=0;
        stackNode *temp = top;
        while (temp != NULL) {
            info+=param+to_string(cont)+"[label=< <b>"+temp->data->type+"</b> <br align=\"left\"/> Palabra buscada: "+temp->data->search+" <br align=\"left\"/> Remplazado por: "+temp->data->update+" <br align=\"left\"/> Estado: "+to_string(temp->data->status)+" <br align=\"left\"/> Palabra: "+temp->data->letra+" <br align=\"left\"/> Posición: "+to_string(temp->data->position)+" <br align=\"left\"/> >]; \n";
            temp = temp->next;
            cont++;
        }
        if(cont!=0) {
            int i=0;
            for (i = 0; i < cont-1 ; i++) {
                info += param + to_string(i) + "->";
            }
            info += param + to_string(i) ;
        }
        return info;
    }
};

class linkedList{
private:
    stackNode *header;
    stackNode *tail;
    int size;
public:
    linkedList(){
        header=NULL;
        tail=NULL;
        size=0;
    }
    void append(stackNode *node){
        tail->next=node;
        tail=node;
        size++;
    }
    void prepend(stackNode *node){
        stackNode *temp=header;
        header=node;
        node->next=temp;
        size++;
    }
    void addData(Log *log, bool mode){
        int cont=0;
        string param;
        string compare;
        stackNode *node=new stackNode(log);
        stackNode *current=header;

        if(header==NULL){
            header=node;
            tail=node;
            size++;
        }
        else{
            if(mode){
                param=node->data->search;
                compare=current->data->search;
            }
            else{
                param=node->data->update;
                compare=current->data->update;
            }

            stackNode *prev;
            while(current!=NULL&&param<=compare){
                prev=current;
                current=current->next;
                cont++;
            }
            if(cont==0){
                append(node);
            }
            else if(cont==size){
                prepend(node);
            }

            else{
                prev->next=node;
                node->next=current;
                size++;
            }
        }
    }
    string thirdReport(string param){
        string info="";
        int cont=0;
        stackNode *temp = header;
        while (temp != NULL) {
            if(param=="x"){
                info+=param+to_string(cont)+"[label=< "+temp->data->search+" <br align=\"left\"/> Remplazada por: "+temp->data->update+" <br align=\"left\"/> >]; \n";
            }
            else{
                info+=param+to_string(cont)+"[label=< "+temp->data->update+" <br align=\"left\"/> Remplazo a: "+temp->data->search+" <br align=\"left\"/> >]; \n";
            }
            temp = temp->next;
            cont++;
        }
        if(cont!=0) {
            int i=0;
            for (i = 0; i < cont-1 ; i++) {
                info += param + to_string(i) + "->";
            }
            info += param + to_string(i) ;
        }
        return info;
    }

};

class Data{
public:
    char data;
    int x=0;
    int y=0;
    Data(){}
    Data(char data){
        this->data=data;
    }
};
class Node{
public:
    Data *data;
    Node *next;
    Node *previous;
    Node(Data *data){
        this->data=data;
        next=NULL;
        previous=NULL;
    }
};
class doubleLinked{
private:
    Node *header;
    Node *tail;
    int size;
public:
    stack *green=new stack();
    stack *red=new stack();

    doubleLinked(){
        header=NULL;
        tail=NULL;
        size=0;
    }
    void cleanList(){
        header=NULL;
        tail=NULL;
        size=0;
    }
    void append(Data *data){
        Node *node=new Node(data);
        if(header==NULL){
            header=node;
            tail=node;
        }
        else{
            tail->next=node;
            node->previous=tail;
            tail=node;

        }
        size++;
    }
    void prepend(Data *data){
        Node *node=new Node(data);
        if(header==NULL){
            header=node;
            tail=node;
        }
        else{
            header->previous=node;
            node->next=header;
            header=node;

        }
        size++;
    }
    void addData(int position, Data *data ){
        if(position<1||position>size+1){
            return;
        }
        else if(position==1){
            prepend(data);
        }
        else if(position==size+1){
            append(data);
        }
        else if(header!=NULL){
            Node *node=new Node(data);
            Node *current=header;
            for(int i=1;i<position;i++){
                current=current->next;
            }
            current->previous->next=node;
            node->previous=current->previous;

            node->next=current;
            current->previous=node;

            size++;
        }
    }
    void deleteFirst(){
        if(header->next==NULL){
            delete header;
            header=NULL;
            tail=NULL;
            size--;
        }
        else if(header!=NULL){
            header=header->next;
            delete header->previous;
            header->previous=NULL;
            size--;
        }
    }
    void deleteLast(){
        if(header->next==NULL){
            delete header;
            header=NULL;
            tail=NULL;
            size--;
        }
        else if(header!=NULL){
            tail=tail->previous;
            delete tail->next;
            tail->next=NULL;
            size--;
        }
    }
    void deleteAt(int position){
        if(position<1||position>size+1){
            cout<<"HEREEEE";
            return;
        }
        else if(position==1){
            deleteFirst();
        }
        else if(position==size){
            deleteLast();
        }
        else if(header!=NULL){
            Node *current=header;
            for(int i=1;i<position;i++){
                current=current->next;
            }
            current->previous->next=current->next;
            current->next->previous=current->previous;
            delete current;
            size--;


        }
    }
    int updateAt(string search,string update){
        int size=1;

        int start=0;
        int end=0;

        int position=0;

        int current=0;

        int found=0;

        Node *temp=header;
        int n = search.length();
        char char_array[n + 1];
        strcpy(char_array, search.c_str());

        int n2 = update.length();
        char char_array2[n2 + 1];
        strcpy(char_array2, update.c_str());


        while(temp!=NULL){
            switch(current){
                case 0:
                    if(temp->data->data==char_array[position]&&temp->data->data!=' '){
                        start=size;
                        position++;
                        current=1;
                    }
                    else{
                        current=2;
                    }

                    break;
                case 1:
                    if(temp->data->data!=char_array[position]){
                        end=size-1;
                        int check=end-start;
                        if(check+1==n){
                            if(temp->data->data==' '||temp->data->data==','||temp->data->data==';'||temp->data->data=='.'||temp->data->data=='\n'||temp->data->data=='\t'||temp->data->data=='\r'){
                                for(int i=0;i<n;i++) {
                                    deleteAt(start);
                                    size--;
                                }
                                int position=start;
                                for(int i=0;i<n2;i++) {
                                    Data *data=new Data(char_array2[i]);
                                    addData(position,data);
                                    position++;
                                    size++;
                                }
                                found++;
                            }
                        }
                        start=0;
                        end=0;
                        current=0;
                        position=0;

                    }else{
                        position++;
                    }
                    break;
                case 2:
                    if(temp->data->data==' '){
                        current=0;
                    }
                    break;
            }
            temp=temp->next;
            size++;
        }
        return found;
    }
    int positionX(int y) {
        int x = 0;
        Node *temp = header;
        while (temp != NULL) {
            if (temp->data->y == y) {
                if (temp->data->x > x) {
                    x = temp->data->x;
                }
            }
            temp = temp->next;
        }
        return x;
    }
    char checkEnter(int y) {
        int x=0;
        char data;
        Node *temp = header;
        while (temp != NULL) {
            if (temp->data->y == y) {
                if(temp->data->x>x){
                    x=temp->data->x;
                    data=temp->data->data;
                }
            }
            temp = temp->next;
        }
        return data;
    }
    int positionCursor(int x,int y) {
        int size = 0;
        Node *temp = header;
        while (temp != NULL) {
            if (temp->data->y == y && temp->data->x == x) {
                size++;
                return size;
            }
            temp = temp->next;
            size++;
        }
        return size;
    }
    char positionChar(int x,int y) {
        char info;
        Node *temp = header;
        while (temp != NULL) {
            if (temp->data->y == y && temp->data->x == x) {
                return temp->data->data;
            }
            temp = temp->next;
        }
    }
    string copy(doubleLinked *list){
        string concat="";
        Node *temp=list->header;
        while(temp!=NULL){
            concat+=temp->data->data;
            temp=temp->next;
        }
        return concat;
    }
    doubleLinked *paste(string copy){
        int size=1;
        doubleLinked *aux=new doubleLinked();

        int n = copy.length();

        char char_array[n + 1];
        strcpy(char_array, copy.c_str());
        for(int i=0;i<n;i++){
            Data *info=new Data(char_array[i]);
            aux->addData(size,info);
            size++;
        }
        return aux;
    }
    void showData(){
        int size=1;

        int x=2;
        int y=4;
        char input;
        Node *temp=header;
        while(temp!=NULL){
            if(temp->data->data=='\r'||temp->data->data=='\n'){
                x++;
                temp->data->y=y;
                temp->data->x=x;
                y++;
                x=2;
            }
            else{
                if(x==75){
                        x=2;
                        y++;
                }
                x++;
                temp->data->y=y;
                temp->data->x=x;
                gotoxy(x,y);
                cout<<temp->data->data;
            }
            temp=temp->next;
            size++;
        }

    }
    string firstReport() {
        string info="";
        int cont=0;
        Node *temp = header;
        info+= "rankdir=LR; node [ shape=square ];  ";
        while (temp != NULL) {
            info+="n_"+to_string(cont)+"[label=\""+temp->data->data+"\"]; \n";
            temp = temp->next;
            cont++;
        }
        if(cont!=0) {
            int i=0;
            for (i = 0; i < cont-1 ; i++) {
              info += "n_" + to_string(i) + "->";
            }
            info += "n_" + to_string(i) ;
        }
        return info;
    }

};
void searchReplace(){
    for(int i=0;i<70;i++){
        gotoxy(i,1);
        cout<<" ";
    }
    gotoxy(8,1);
    cout<<"^w(Buscar y Reemplazar)";
    gotoxy(8,2);
    cout<<">";
}
void openFile(){
    for(int i=0;i<70;i++) {
        gotoxy(i, 1);
        cout << " ";
        gotoxy(i,2);
        cout<<" ";
    }
    gotoxy(8,1);
    cout<<"Escribe el nombre del archivo a utilizar:";
    gotoxy(8,2);
    cout<<">";

}
void reports(){
    for(int i=0;i<70;i++){
        gotoxy(i,1);
        cout<<" ";
    }
    gotoxy(8,1);
    cout<<"^c(Reportes)";
    gotoxy(8,2);
    cout<<">";
    gotoxy(9,2);
    cout<<"1. Listado caracteres";
    gotoxy(20,2);
    cout<<"2. Log de cambios";
    gotoxy(40,2);
    cout<<"3. Buscar/remplazar alfabetico";
}
void mainMenu() {
    gotoxy(7, 6);
    cout<<"UNIVERSIDAD DE SAN CARLOS DE GUATEMALA";
    gotoxy(7, 7);
    cout<<"FACULTAD DE INGENIERIA";
    gotoxy(7, 8);
    cout<<"ESTRUCTURAS DE DATOS";
    gotoxy(7, 9);
    cout<<"PRACTICA 1";
    gotoxy(7, 10);
    cout<<"JULIAN ISAAC MALDONADO LOPEZ";
    gotoxy(7, 11);
    cout<<"201806839";
    gotoxy(7, 18);
    cout<<"MENU";
    gotoxy(7, 19);
    cout<<"1. Crear archivo";
    gotoxy(7, 20);
    cout<<"2. Abrir archivo";
    gotoxy(7, 21);
    cout<<"3. Archivos recientes";
    gotoxy(7, 22);
    cout<<"4. Salir";
}
void newFile(){
    for(int i=0;i<70;i++){
        gotoxy(i,1);
        cout<<" ";
        gotoxy(i,2);
        cout<<" ";
    }
    gotoxy(8,1);
    cout<<"^w(Buscar y Reemplazar)";
    gotoxy(38,1);
    cout<<"^c(Reportes)";
    gotoxy(58,1);
    cout<<"^s(Guardar)";
}
void erase() {
    for (int i = 3; i < 76; i++) {
        for (int k = 4; k < 25; k++) {
            gotoxy(i, k);
            cout << " ";
            gotoxy(i, k);
            cout << " ";
        }
    }
    for (int i = 8; i < 75; i++) {
        gotoxy(i,1);
        cout<<" ";
        gotoxy(i,2);
        cout << " ";
    }
}
void margins(){
    for(int i=2;i<77;i++) {
        gotoxy(i, 3);
        printf("%c", 205);
        gotoxy(i, 25);
        printf("%c", 205);
    }
    for(int i=4;i<25;i++){
        gotoxy(2,i);
        printf("%c",186);
        gotoxy(76,i);
        printf("%c",186);
    }

}

int main() {
    hideCursor();

    doubleLinked *list=new doubleLinked();
    circularList *circular=new circularList();
    Log *info;
    ofstream file;

    bool active = true;
    bool flag=false;
    bool exit=false;

    int current = 0;
    int cursor = 1;
    int x = 3;
    int y = 4;
    int x_=9;
    int y_=2;
    int currentNewFile=0;
    int result;
    int acci=0;

    string search;
    string update;
    string copy;

    string s;
    string sTotal;
    string path="C:\\Users\\Isaac Maldonado\\Desktop\\";
    string name;

    char found;

    while (active) {
           char input;
           switch (current) {
               case 0:
                   margins();
                   mainMenu();
                   input = getch();
                   switch (input) {
                       case '1':
                           current = 1;
                           erase();
                           newFile();
                           break;
                       case '2':
                           x_=9;
                           current=2;
                           erase();
                           openFile();
                           break;
                       case '3':
                            current=3;
                            erase();
                            circular->showData();
                           break;
                       case '4':
                           active = false;
                           break;
                   }

                   break;

               case 1:
                   switch (currentNewFile){
                       case 0:
                           if(x==76){
                               x=3;
                               y++;
                           }
                           gotoxy(x,y);
                           cout<<"|";
                           if (kbhit()){
                               input = getch();
                               acci=input;
                               if (input == DOWN) {
                                   if (y < 25) {
                                       int aux;
                                       int yTemp=y+1;
                                       aux=list->positionX(yTemp);
                                       if(aux!=0){
                                           y++;
                                           x=aux;
                                           if(x==77){
                                               cursor=list->positionCursor(76,y)+1;
                                           }
                                           else{
                                               cursor=list->positionCursor(x,y);
                                           }
                                       }
                                   }
                               }
                               else if (input == UP){
                                   if (y > 4) {
                                       int yTemp=y-1;
                                       int aux;
                                       aux=list->positionX(yTemp);
                                       if(aux!=1){
                                           y--;
                                           x=aux;
                                           if(x==77){
                                              cursor=list->positionCursor(76,y)+1;
                                           }
                                           else{
                                               cursor=list->positionCursor(x,y);
                                           }
                                       }

                                   }
                               }
                               else if (input == RIGHT) {
                                   char result=list->checkEnter(y);
                                   if (x < 75) {
                                       int aux;
                                       int xTemp=x+1;
                                       aux=list->positionX(y);
                                       if(xTemp<=aux+1) {
                                           if (xTemp < aux + 1) {
                                               x++;
                                               cursor++;
                                           } else if (xTemp == aux + 1 && result != '\r') {
                                               x++;
                                               cursor++;
                                           }
                                       }

                                   }
                               }
                               else if (input == LEFT) {
                                  if (x > 3) {
                                       int aux;
                                       int xTemp=x-1;
                                       aux=list->positionX(y);
                                       if(xTemp<aux+1){
                                           x--;
                                           cursor--;

                                       }

                                   }
                               }
                               //Reports
                               else if(acci==19){
                                   currentNewFile=5;
                               }
                                   //Delete
                               else if(acci==8){
                                   bool check=true;
                                   int aux;
                                   if(x==3&&y!=4){
                                       y--;
                                       x=list->positionX(y)+2;
                                      check=false;
                                   }
                                   aux=list->positionCursor(x-1,y);
                                   if(aux!=0){
                                       if(flag){
                                           list->red->cleanStack();
                                           list->green->cleanStack();
                                           flag=false;
                                       }
                                       found=list->positionChar(x-1,y);
                                       info=new Log(found,aux,false);
                                       info->type="delete";
                                       list->green->push(info);
                                       list->deleteAt(aux);
                                      if(check){
                                           cursor--;
                                           x--;
                                       }
                                       else{
                                            x=x-2;
                                            cursor--;
                                       }
                                   }
                               }
                                   //Exit
                               else if (input == 24) {
                                   exit=true;
                                   erase();
                                   current = 0;
                                   x = 3;
                                   y = 4;
                                   list->cleanList();
                                   cursor=1;
                               }
                                    //Search-Update
                               else if(input==23) {
                                   exit=true;
                                   update="";
                                   search="";
                                   y_=2;
                                   x_=9;

                                   currentNewFile=1;
                               }
                                   //Enter-Return
                               else if (input == '\r') {
                                   if(y<25) {
                                       if(flag){
                                           list->red->cleanStack();
                                           list->green->cleanStack();
                                           flag=false;
                                       }
                                       Data *data=new Data(input);
                                       list->addData(cursor,data);
                                       info=new Log(data->data,cursor,false);
                                       info->type="add";
                                       list->green->push(info);
                                       cursor++;
                                       y++;
                                       x=3;

                                   }
                               }
                               //ctr+y
                               else if(input==25){
                                   if(list->red->stackSize()!=0) {
                                       stackNode *instance = new stackNode(list->red->pop());
                                       if (instance->data->type == "s/r") {
                                           copy=list->copy(list);
                                           doubleLinked *aux=new doubleLinked();
                                           aux=list->paste(instance->data->list);
                                           aux->green=list->green;
                                           aux->red=list->red;
                                           list=aux;
                                           instance->data->status=false;
                                           instance->data->list=copy;
                                           list->green->push(instance->data);

                                       }
                                       if (instance->data->type == "add") {
                                           Data *data=new Data(instance->data->letra);
                                           list->addData(instance->data->position,data);
                                           instance->data->status = false;
                                           list->green->push(instance->data);


                                       }
                                       if(instance->data->type == "delete"){
                                           list->deleteAt(instance->data->position);
                                           instance->data->status = false;
                                           list->green->push(instance->data);
                                       }
                                       x=3;
                                       y=4;
                                       cursor=1;
                                   }
                               }
                               //ctr+z
                               else if(input ==26) {
                                   flag=true;
                                if (list->green->stackSize() != 0) {
                                       stackNode *instance = new stackNode(list->green->pop());

                                       if (instance->data->type == "s/r") {
                                           copy=list->copy(list);

                                           doubleLinked *aux=new doubleLinked();
                                           aux=list->paste(instance->data->list);
                                           aux->green=list->green;
                                           aux->red=list->red;
                                           list=aux;
                                           instance->data->status=true;
                                           instance->data->list=copy;
                                           list->red->push(instance->data);

                                       }
                                       if (instance->data->type == "add") {
                                           list->deleteAt(instance->data->position);
                                           instance->data->status = true;
                                           list->red->push(instance->data);
                                       }
                                        if(instance->data->type == "delete"){
                                           Data *data=new Data(instance->data->letra);
                                           list->addData(instance->data->position,data);
                                           instance->data->status = true;
                                           list->red->push(instance->data);

                                       }
                                    x=3;
                                    y=4;
                                    cursor=1;

                                   }
                               }
                               else {
                                   if (acci != -32) {
                                       if (x < 77) {
                                           if (x == 76 || x == 75) {
                                               x = 2;
                                               if (y < 25) {
                                                   y++;
                                               }
                                           }
                                           if (y < 25) {
                                               if(flag){
                                                   list->red->cleanStack();
                                                   list->green->cleanStack();
                                                   flag=false;
                                               }
                                               Data *data = new Data(input);
                                               list->addData(cursor, data);
                                               info = new Log(data->data, cursor, false);
                                               info->type = "add";
                                               list->green->push(info);
                                               x++;
                                               cursor++;
                                           }
                                       }
                                   }

                               }
                               if(!exit) {
                                 system("cls");
                                   list->showData();
                                   margins();
                                   newFile();
                               }
                               else {
                                   exit = false;
                               }

                           }

                           break;
                       case 1:
                            searchReplace();
                            input=getch();
                            acci=input;
                            if(acci==24){
                                currentNewFile=0;
                                newFile();
                                list->showData();
                            }
                            else if(input=='\r'){
                                currentNewFile=2;
                                gotoxy(x_,y_);
                                cout<<"/";
                                x_++;
                            }
                            else{
                                gotoxy(x_,y_);
                                cout<<input;
                                search+=input;
                                x_++;
                            }
                       break;
                       case 2:
                           input=getch();
                           acci=input;
                           if(acci==24){
                               currentNewFile=0;
                               newFile();
                               list->showData();

                           }
                           else if(input=='\r'){
                               currentNewFile=3;
                           }
                           else{
                               gotoxy(x_,y_);
                               cout<<input;
                               update+=input;
                               x_++;
                           }
                           break;
                       case 3:
                           copy=list->copy(list);
                           result=list->updateAt(search, update);
                           if(result>0){

                               if(flag){
                                   list->red->cleanStack();
                                   list->green->cleanStack();
                                   flag=false;
                               }
                               info=new Log(search,update,false,copy);
                               info->type="s/r"; //----------->Search/Replace
                               list->green->push(info);
                               x=3;
                               y=4;
                               cursor=1;
                           }
                           gotoxy(x_,2);
                           cout<<" Result: "<<result;
                           currentNewFile=4;
                           break;
                       case 4:
                           input=getch();
                           acci=input;
                           if(acci==24){
                               system("cls");
                               newFile();
                               margins();
                               list->showData();
                               x=3;
                               y=4;
                               cursor=1;
                               currentNewFile=0;
                          }
                           break;
                       case 5:
                           reports();
                           input=getch();
                           acci=input;
                           if(acci==24){
                               currentNewFile=0;
                               newFile();
                           }
                           switch (input){
                               case '1':
                                   file.open("C:/Users/Isaac Maldonado/Desktop/save.dot",ios::out);
                                   file<<"digraph L { ";
                                   file<<list->firstReport();
                                   file<<  "}";
                                   file.close();
                                   system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && dot -Tpng save.dot -o save.png");
                                   system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && start save.png ");
                                   break;
                               case '2':
                                   file.open("C:/Users/Isaac Maldonado/Desktop/save.dot",ios::out);
                                   file<<"digraph L { ";
                                   file<<"rankdir=LR; node [ shape=square ];  ";
                                   file<<list->green->secondReport("x");
                                   file<<"\n";
                                   file<<list->red->secondReport("y");
                                   file<<  "}";
                                   file.close();
                                   system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && dot -Tpng save.dot -o save.png");
                                   system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && start save.png ");
                                   break;
                               case '3':
                                 file.open("C:/Users/Isaac Maldonado/Desktop/save.dot",ios::out);
                                 file<<"digraph L { ";
                                file<<"rankdir=LR; node [ shape=square ];  ";

                                 linkedList *aux=new linkedList();
                                 stack *auxStack;
                                 auxStack=list->green;
                                 while(auxStack->stackSize()>0){
                                         Log *temp;
                                         temp=auxStack->pop();
                                         if(temp->type=="s/r") {
                                             aux->addData(temp, false);
                                         }
                                 }
                                 file<<aux->thirdReport("x");
                                 file<<"\n";
                                 stack *auxStack2;
                                 auxStack2=list->green;
                                 while(auxStack2->stackSize()>0){
                                       Log *temp;
                                       temp=auxStack2->pop();
                                       if(temp->type=="s/r") {
                                           aux->addData(temp, true);
                                       }
                                   }
                                   file<<aux->thirdReport("y");

                                file<<  "}";
                                file.close();
                              system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && dot -Tpng save.dot -o save.png");
                              system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && start save.png ");

                                   break;
                           }
                           break;

                   }


                    break;
               case 2:

                   input=getch();
                   acci=input;
                   if (acci == 24) {
                       system("cls");
                       current = 0;;
                       x = 3;
                       y = 4;
                   }
                   else if(input=='\r'){
                       current=5;
                   }
                   else{
                       gotoxy(x_,2);
                       cout<<input;
                       name+=input;
                       x_++;
                   }

                   break;
               case 3:
                   circular->showData();
                   input=getch();
                   acci=input;
                   if (acci == 24) {
                       system("cls");
                       current = 0;;
                       x = 3;
                       y = 4;
                   }
                   else if(input=='x'){
                       file.open("C:/Users/Isaac Maldonado/Desktop/save.dot",ios::out);
                       file<<"digraph L { ";
                       file<<circular->fourthReport();
                       file<<  "}";
                       file.close();
                       system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && dot -Tpng save.dot -o save.png");
                       system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && start save.png ");
                   }
               break;
               case 5:
                   ifstream in(path+name);
                   if(in.fail()){
                       openFile();
                       x_=9;
                       current=2;
                       name="";

                   }
                   else {
                       while (getline(in, s)) {
                           sTotal += (s + "\r");
                       }
                       list=list->paste(sTotal);
                       list->showData();
                       newFile();
                       current = 1;
                       if(!circular->search(name)){
                           circularNode *node=new circularNode(name);
                           circular->prepend(node);
                       }
                       sTotal="";

                   }
                   in.close();
                   break;


            }



    }
    return 0;
}