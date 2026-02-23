#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;


class motorVehicle{
    private:
        string type;
        string registration_number;
        string brand;
        string model;
        string color;
        int year;
        float mileage;
    public:
        motorVehicle() : 
          type(" ") , registration_number(" ") , brand(" ") , model(" ") , color(" ") , year(0) , mileage(0.0){}

        motorVehicle(string t , string r , string b , string md , string c , int y , float m) : 
          type(t) , registration_number(r) , brand(b) , model(md) , color(c) , year(y) , mileage(m){}

        virtual void display() const {
             cout << setw(6) << type << " : "
                  << brand << " " 
                  << model << " " 
                  << year << " " 
                  << registration_number << " ";
        }
        virtual motorVehicle* deep_copy() const = 0;

        virtual void save_specific_details(ofstream& file) = 0;

        
        static void enter_details(string& reg , string& br , string& md , string& col , int& year , float& mil){
            cin.ignore();
            cout << "Enter Brand of Vehicle : ";
            getline(cin,br);
            cout << "Enter Model of Vehicle : ";
            getline(cin,md);

            do{
            cout << "Enter Registration Number of Vehicle (ABC-1234) : ";
            getline(cin,reg);
            }while(!(motorVehicle :: is_valid_reg_no(reg)));

            cout << "Enter Color of Vehicle : ";
            getline(cin,col);

            do{
            cout << "Enter Manufacturing Year of Vehicle : ";
            cin >> year;
            }while(!(motorVehicle :: is_valid_year(year)));

            do{
            cout << "Enter Mileage of Vehicle (in Km/h) : ";
            cin >> mil;
            }while(!(motorVehicle :: is_valid_mileage(mil)));
        }

        static bool is_valid_reg_no(const string& reg){
            if(reg.length() != 8){return false;}
            for(int i=0;i<3;i++){
                if(reg[i] < 'A' || reg[i] > 'Z'){return false;}
            }
            if(reg[3] != '-'){return false;}
            for(int i=4;i<8;i++){
                if(reg[i] < '0' || reg[i] > '9'){return false;}
            }
            return true;
        }

        static bool is_valid_year(int y){
            if(y >= 1980 && y <= 2025){return true;}
            cout << "Invalid Year.\n";
            return false;
        }

        static bool is_valid_mileage(float m){
            if(m > 0.0 && m < 100.0){return true;}
            cout << "Invalid Mileage.\n";
            return false;
        }

        const string& get_type() {
            return this->type;
        }

        const string& get_reg() const {
            return this->registration_number;
        }
        
        const string& get_brand() const {
            return this->brand;
        }

        const string& get_model() const {
            return this->model;
        }

        const string& get_color() const {
            return this->color;
        }

        int get_year() const {
            return this->year;
        }

        float get_mileage() const {
            return this->mileage;
        }

        virtual ~motorVehicle() = default;
           

};

class Car : public motorVehicle{
    private:
        int doors;
        string fuel_type;
    public:
        Car() : doors(0) , fuel_type(" ") {}

        Car(string t , string r , string b , string md , string c , string f , int y , float m , int d) :
            motorVehicle("Car" , r , b , md , c , y , m) , doors(d) , fuel_type(f) {}

        Car(const Car& other){
            *this = other;
        }

        void display() const override{
            motorVehicle :: display();
            cout << " Fuel:" << fuel_type << '\n';
        }

        void save_specific_details(ofstream& file) override {
            file << this->doors << ','
                 << this->fuel_type << ',';
        }

        motorVehicle* deep_copy() const override {
            return new Car(*this);
        }

        ~Car() override = default;
    };

class Bike : public motorVehicle{
    private:
        string body_type;
        float engine_CC;
    public:
        Bike() : body_type(" ") , engine_CC(0) {}

        Bike(string t , string r , string b , string md , string c , string bt , int y , float m , float eng) :
             motorVehicle("Bike" , r , b , md , c , y , m) , body_type(bt) , engine_CC(eng) {}

        Bike(const Bike& other){
            *this = other;
        }

        void display() const override{
            motorVehicle :: display();
            cout << " Engine:" << engine_CC << "CC\n"; 
        }

        void save_specific_details(ofstream& file) override {
            file << this->body_type << ','
                 << this->engine_CC << ',';
        }

        motorVehicle* deep_copy() const override {
            return new Bike(*this);
        }

        ~Bike() override = default; 
};

class Truck : public motorVehicle{
    private:
        float weight;
        float shipment_capacity;
    public:
        Truck() : weight(0.0) , shipment_capacity(0.0) {}

        Truck(string t , string r , string b , string md , string c , int y , float m , float wei , float ship_cap) : 
            motorVehicle("Truck" , r , b , md , c , y , m) , weight(wei) , shipment_capacity(ship_cap) {}

        Truck(const Truck& other){
            *this = other;
        }

        void display() const override{
            motorVehicle :: display();
            cout << " Weight:" << weight << "-Tons\n";
        }

        void save_specific_details(ofstream& file) override {
            file << this->weight << ','
                 << this->shipment_capacity << ',';
        }

        motorVehicle* deep_copy() const override {
            return new Truck(*this);
        }

        ~Truck() override = default;

};

class Garage{
    private:
        motorVehicle** vehicles;
        int current_vehicles;
        int garage_capacity;
    public:
        Garage(){}

        void show_all_vehicles(){
                if(current_vehicles == 0){cout << "Garage is Empty.\n"; return;}
                for(int i=0;i<current_vehicles;i++){
                vehicles[i]->display();
            }
        }

        void add_car(){
            if(current_vehicles == garage_capacity){
                cout << "Garage is Full.\nDo you wish to expand ? (y/n) : ";
                if(expand_garage_ans()){expand_garage();}
                else{return;}
            }

            string reg , br , md , col , f;
            int y , d;
            float m;
            motorVehicle :: enter_details(reg,br,md,col,y,m);
            cout << "Enter Fuel Type of Car : ";
            cin >> f;
            cin.ignore();
            cout << "Enter Number of Doors : ";
            cin >> d;
            if(registration_number_already_exists(reg)){cout << "Vehicle of this Registration Number Already Exists.\n";return;}
            if(d != 2 && d != 4){cout << "\nBro, Cars can have either 2 or 4 Doors.\n"; return;}
            vehicles[current_vehicles] = new Car("Car",reg,br,md,col,f,y,m,d);
            current_vehicles++;
            cout << "\nCar Added Successfully.\n";
        }

        void add_bike(){
            if(current_vehicles == garage_capacity){
                cout << "Garage is Full.\nDo you wish to expand ? (y/n) : ";
                if(expand_garage_ans()){expand_garage();}
                else{return;}
            }

            string reg , br , md , col , body;
            int y , eng_CC;
            float m;
            motorVehicle :: enter_details(reg,br,md,col,y,m);
            cin.ignore();
            cout << "Enter Body Type of Bike : ";
            getline(cin,body);
            cout << "Enter Engine CC (Cubic Centimeter) : ";
            cin >> eng_CC;
            if(registration_number_already_exists(reg)){cout << "Vehicle of this Registration Number Already Exists.\n";return;}
            if(eng_CC > 2500){cout << "\nBro, Bike Engine cannot be more than 2500 CC.\n"; return;}
            vehicles[current_vehicles] = new Bike("Bike",reg,br,md,col,body,y,m,eng_CC);
            current_vehicles++;
            cout << "\nBike Added Successfully.\n";
        }

        void add_truck(){
             if(current_vehicles == garage_capacity){
                cout << "Garage is Full.\nDo you wish to expand ? (y/n) : ";
                if(expand_garage_ans()){expand_garage();}
                else{return;}
            }

            string reg , br , md , col;
            int y;
            float m , weight , ship_cap;
            motorVehicle :: enter_details(reg,br,md,col,y,m);
            cout << "Enter Weight of Truck (in Tons) : ";
            cin >> weight;
            cout << "Enter Max Shipment Capacity of Truck (in Tons) : ";
            cin >> ship_cap;
            if(registration_number_already_exists(reg)){cout << "\nVehicle of this Registration Number Already Exists.\nVehicle Not Added.\n";return;}
            if(ship_cap >= weight){cout << "\nBro, Shipment Capacity can't be Equal or Greater to Weight.\n"; return;}
            vehicles[current_vehicles] = new Truck("Truck",reg,br,md,col,y,m,weight,ship_cap);
            current_vehicles++;
            cout << "\nTruck Added Successfully.\n";
        }

        void expand_garage(){
            motorVehicle** new_vehicles = new motorVehicle*[garage_capacity*2];
            for(int i=0;i<current_vehicles;i++){
               new_vehicles[i] = vehicles[i]->deep_copy();
            }
            for(int i=0;i<current_vehicles;i++){
                delete vehicles[i];
            }
            delete[] vehicles;
            vehicles = new_vehicles;
            garage_capacity = garage_capacity*2;
        }

        void see_specific_brand_vehicles(){
            string n;
            cout << "Enter Brand : ";
            cin.ignore();
            getline(cin,n);
            cout << '\n';
            for(int i=0;i<current_vehicles;i++){
                if(n == this->vehicles[i]->get_brand()){
                    vehicles[i]->display();
                }
            }
        }

        void save_data_to_file(){
            ofstream save_file("vehicles.txt");
           
            if(!save_file.is_open()){cout << "Error Opening File.\n"; return;}
            save_file << current_vehicles << endl << garage_capacity << endl;
            for(int i=0;i<current_vehicles;i++){
                save_file << vehicles[i]->get_type() << ','
                          << vehicles[i]->get_reg() << ','
                          << vehicles[i]->get_brand() << ','
                          << vehicles[i]->get_model() << ','
                          << vehicles[i]->get_color() << ','
                          << vehicles[i]->get_year() << ','
                          << vehicles[i]->get_mileage() << ',';
                vehicles[i]->save_specific_details(save_file);
                save_file << endl;
            }

            save_file.close();
            cout << "Garage Saved Successfully.\n";
        }

        void load_data_from_file(){

            int current_v , max_v;
            ifstream load_file("vehicles.txt");
            
            if(!load_file.is_open()){cout << "Error Opening File.\n"; return;}

            string type,reg,brand,model,color;
            int year;
            float mileage;

            load_file >> current_v >> max_v;
            load_file.ignore();

            current_vehicles = current_v;
            garage_capacity = max_v;
            vehicles = new motorVehicle*[garage_capacity];

            for(int i=0;i<current_vehicles;i++){
                getline(load_file,type,',');
                getline(load_file,reg,',');
                getline(load_file,brand,',');
                getline(load_file,model,',');
                getline(load_file,color,',');
                load_file >> year;
                load_file.ignore();
                load_file >> mileage;
                load_file.ignore();

                if(type == "Car" || type == "car"){
                    int doors;
                    string fuel;
                    load_file >> doors;
                    load_file.ignore();
                    getline(load_file,fuel,',');
                    load_file.ignore();
                    vehicles[i] = new Car("Car",reg,brand,model,color,fuel,year,mileage,doors);
                }

                else if(type == "Bike" || type == "bike"){
                    string body;
                    float engine_CC;
                    getline(load_file,body,',');
                    load_file >> engine_CC;
                    load_file.ignore();
                    load_file.ignore();
                    vehicles[i] = new Bike("Bike",reg,brand,model,color,body,year,mileage,engine_CC);
                }

                else if(type == "Truck" || type == "truck"){
                    float weight,shipment_capacity;
                    load_file >> weight;
                    load_file.ignore();
                    load_file >> shipment_capacity;
                    load_file.ignore();
                    load_file.ignore();
                    vehicles[i] = new Truck("Truck",reg,brand,model,color,year,mileage,weight,shipment_capacity);
                }
            }

            load_file.close();
            cout << "\nGarage loaded Successfully.\n";
        }

        bool registration_number_already_exists(const string& reg){
            for(int i=0;i<current_vehicles;i++){
                if(vehicles[i]->get_reg() == reg){return true;}
            }
            return false;
        }

        bool expand_garage_ans(){
            char ch;
            cin >> ch;
            if(ch == 'y' || ch == 'Y'){cout << "Garage Expanded.\n\n";return true;}
            return false;
        }

        void run(){
            char c;
            do{
                cout << "\nDo you wish to load previous garage ? (y/n) : ";
                cin >> c;
            }while(c != 'n' && c != 'N' && c != 'y' && c != 'Y');

            if(c == 'n' || c == 'N'){
                current_vehicles = 0;
                garage_capacity = 1;
                vehicles = new motorVehicle*[garage_capacity];
            }
            else if(c == 'y' || c == 'Y'){
                load_data_from_file();
            }

            int ch;
            do{
                menu(ch);
            }while(ch != 0);
        }

        void menu(int& ch){
            cout << "\n\n";
            cout << " 1. Show all Vehicles.\n"
                 << " 2. Add Car.\n"
                 << " 3. Add Bike.\n"
                 << " 4. Add Truck.\n"
                 << " 5. See Vehicles of specific Brand.\n"
                 << " 6. Save Garage.\n"
                 << " 0. Exit.\n"
                 << "----------------------------------\n"
                 << "Enter Choice : ";
            cin >> ch;
            cout << '\n';
            switch (ch)
            {
            case 1:
                show_all_vehicles();
                break;
            case 2:
                add_car();
                break;
            case 3:
                add_bike();
                break;
            case 4:
                add_truck();
                break;
            case 5:
                see_specific_brand_vehicles();
                break;
            case 6:
                save_data_to_file();
                break;
            case 0:
                cout << "Shutting Down Garage.\n";
                break;
            
            default:
                cout << "Invalid Choice !!";
                break;
            }
        }

        ~Garage(){
            for(int i=0;i<current_vehicles;i++){
                delete vehicles[i];
            }
            delete[] vehicles;
            vehicles = nullptr;
        }
};


int main(){

    cout << "\n              ==============================| BLACK KNIGHT GARAGE |==============================\n";

    Garage garage;
    garage.run();

    cout << "____________________________________________________________________________________________\n\n";

    return 0;
}


 