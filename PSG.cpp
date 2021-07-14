#include<bits/stdc++.h>
#include<cstring>
#include<cstdlib>
using namespace std;
#define int long long 
#define MP make_pair
#define PB push_back
#define MOD 1000000007
#define fi first
#define se second
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<PII> VPII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;

//forward declearation of the classes
class pay_slip;
class permanent_employee;
class contractual_employee;

//function prototypes
int get_da_rate();
int get_hra_rate();
int get_ma();
int get_ptax();
int get_emp_no();
int search(int ,permanent_employee *);
int search(int,contractual_employee *);
void generate_pa_slip(permanent_employee);
void generate_pa_slip(contractual_employee);
void compute_OT();

class employee{ //BASE CLASS
    protected:
    int emp_no;
    char emp_name[40];
    char emp_add[80];
    char emp_desg[20];
    char emp_dept[20];
    char emp_mob[20];
    char emp_email[50];
    char emp_username[20];
    char emp_pass[20];
    public:
    void getdata();
    void displaydata();
}; //end of base class

void employee::getdata(){
    emp_no=get_emp_no();
    cout<<"\nEnter the name of the employee : ";
    cin.getline(emp_name,40);
    cout<<"\nEnter the adress of the employee : ";
    cin.getline(emp_add,80);
    cout<<"\nEnter the designation of the employee : ";
    cin.getline(emp_desg,20);
    cout<<"\nEnter the department of the employee : ";
    cin.getline(emp_dept,20);
}

void employee::displaydata()
{
    cout<<"\nEmp. No.           : "<<emp_no;
    cout<<"\nName.              : "<<emp_name;
    cout<<"\nAddress            : "<<emp_add;
    cout<<"\nDesignation        : "<<emp_desg;
    cout<<"\nDepartment         : "<<emp_dept;
}

class permanent_employee :public employee{
private:
    char emp_type[10];
    long emp_basic;
    long emp_da;
    long emp_hra;
    int emp_ma;
    long emp_pf;
    long ptax;
    int itax;
    long gross;
    long net;
public:
    void getdata();           //over-ridden fun
    void displaydata();       //over-ridden fun
    void calculate();
    void store_in_file();
    friend int search(int ,permanent_employee *);
    friend void generate_pay_slip(permanent_employee);
    friend void compute_OT();
};

void permanent_employee::getdata()
{
    employee::getdata();                                          //calling base getdata()
    try{                                                          //exception handling for negative basic
        cout<<"\nEnter the basic salary : ";
        cin>>emp_basic;
        if(emp_basic<0)
                throw emp_basic;
    }
    catch(...)
    {
        cout<<"\nBasic should be positive";
        return;
    }
    try{                                                           //exception handling for negative income tax
        cout<<"\nEnter the income tax to be deducted : ";
        cin>>itax;
        if(itax<0)
                throw itax;
    }
    catch(...)
    {
        cout<<"\nIncome Tax should be positive ";
        return;
    }
    calculate();
}

void permanent_employee::calculate(){
    int hra,da;

    strcpy(emp_type,"Permanent");
    da=get_da_rate();
    emp_da=emp_basic*da/100;                                       //da is calculated as a percent of  basic

    hra=get_hra_rate();
    emp_hra=emp_basic*hra/100;                                     //hra is calculated as a percent of  basic

    emp_ma=get_ma();
    emp_pf = (emp_basic + emp_da)*12/100;;                         //pf is calculate as a percentage of basic+da

    ptax = get_ptax();
    gross = emp_basic + emp_da + emp_hra + emp_ma;                 //cal of gross
    net = gross - ptax -itax -emp_pf;                              //cal of net   
}

void permanent_employee::displaydata(){
    employee::displaydata();                                       //calling base display
    cout<<"\nEmployee type          : "<<emp_type;
    cout<<"\nBasic                  : "<<emp_basic;
    cout<<"\nDearness Allowance     : "<<emp_da;
    cout<<"\nHRA                    : "<<emp_hra;
    cout<<"\nMedical Allowance      : "<<emp_ma;
    cout<<"\nPF                     : "<<emp_pf;
    cout<<"\nProfessional tax       : "<<ptax;
    cout<<"\nIncome tax             : "<<itax;
    cout<<"\nIGross Salary          : "<<gross;
    cout<<"\nNet Salary             : "<<net;
}

void permanent_employee::store_in_file(){
    ofstream outfile;
    outfile.open("per_empf",ios::app);                          //open per_empf in append mode
//                                                              //file per_empf stores details of permanent employees
    outfile<<emp_no<<"\n";
    outfile<<emp_name<<"\n";
    outfile<<emp_add<<"\n";
    outfile<<emp_desg<<"\n";
    outfile<<emp_dept<<"\n";
    outfile<<emp_type<<"\n";
    outfile<<emp_basic<<"\n";
    outfile<<emp_da<<"\n";
    outfile<<emp_hra<<"\n";
    outfile<<emp_ma<<"\n";
    outfile<<emp_pf<<"\n";
    outfile<<ptax<<"\n";
    outfile<<itax<<"\n";
    outfile<<gross<<"\n";
    outfile<<net<<"\n";
    outfile.close();                                           //close file
}

class contractual_employee:public employee{                    //derived from base class 
    private:
    char emp_type[12];
    long gross;
    int ptax;
    int itax;
    long net;
public:
    void getdata();           //over-ridden fun
    void displaydata();       //over-ridden fun
    void calculate();
    void store_in_file();
    friend int search(int ,contractual_employee *);
    friend void generate_pay_slip(contractual_employee);
    friend void compute_OT();
};

void contractual_employee::getdata()                             //over-ridden func getdata()
{
    employee::getdata();                                          //calling base getdata()
    try{                                                          //exception handling for negative gross
        cout<<"\nEnter the gross salary : ";
        cin>>gross;
        if(gross<0)
                throw gross;
    }
    catch(...)
    {
        cout<<"\nGross should be positive";
        return;
    }
    try{                                                           //exception handling for negative income tax
        cout<<"\nEnter the income tax to be deducted : ";
        cin>>itax;
        if(itax<0)
                throw itax;
    }
    catch(...)
    {
        cout<<"\nIncome Tax should be positive ";
        return;
    }
    calculate();
}

void contractual_employee::calculate(){
    strcpy(emp_type,"Contractual");
    ptax = get_ptax();
    net = gross - ptax -itax;
}

void contractual_employee::displaydata(){                            //over-ridden displaydata()
    employee::displaydata();                                          //calling base dispalydata
    cout<<"\nEmployee type          : "<<emp_type;
    cout<<"\nGross Salary           : "<<gross;
    cout<<"\nProfessional tax       : "<<ptax;
    cout<<"\nIncome tax             : "<<itax;
    cout<<"\nNet Salary             : "<<net;
}

void contractual_employee::store_in_file(){
    ofstream outfile;
    outfile.open("con_empf",ios::app);                              //open file in append mode
    //                                                              //file per_empf stores details of permanent employees
    outfile<<emp_no<<"\n";
    outfile<<emp_name<<"\n";
    outfile<<emp_add<<"\n";
    outfile<<emp_desg<<"\n";
    outfile<<emp_dept<<"\n";
    outfile<<emp_type<<"\n";
    outfile<<gross<<"\n";
    outfile<<ptax<<"\n";
    outfile<<itax<<"\n";
    outfile<<net<<"\n";
    outfile.close();                                                   //clos file
}

int search(int no,permanent_employee *per){                           //func. defn. for searching permanent employee from file
    ifstream infile;
    permanent_employee p;
    char ch;

    infile.open("per_empf");                                          //open file in read mode
    if(!infile.fail())                                                //checking if file exists
    {
        while (!infile.eof())
        {
            infile>>p.emp_no;
            infile.ignore(1000,'\n');
            infile.getline(p.emp_name,40);
            infile.getline(p.emp_add,80);
            infile.getline(p.emp_desg,20);
            infile.getline(p.emp_dept,20);
            infile>>p.emp_type>>p.emp_basic>>p.emp_da>>p.emp_hra>>p.emp_ma>>p.emp_pf>>p.ptax>>p.itax>>p.gross>>p.net;
            if(no==p.emp_no){                                        //look for a match
                *per=p;                                              //set pointer to the object if found
                return 1;                                            //return true
            }
        }
    }
    return 0;                                                         //return false if not found
}

int search(int no,contractual_employee *con){                           //func. defn. for searching contractual_employee from file
    ifstream infile;
    contractual_employee p;
    char ch;

    infile.open("con_empf");                                          //open file in read mode
    if(!infile.fail())                                                //checking if file exists
    {
        while (!infile.eof())
        {
            infile>>p.emp_no;
            infile.ignore(1000,'\n');
            infile.getline(p.emp_name,40);
            infile.getline(p.emp_add,80);
            infile.getline(p.emp_desg,20);
            infile.getline(p.emp_dept,20);
            infile>>p.emp_type>>p.gross>>p.ptax>>p.itax>>p.net;
            if(no==p.emp_no){                                        //look for a match
                *con=p;                                              //set pointer to the object if found
                return 1;                                            //return true
            }
        }
    }
    return 0;                                                         //return false if not found
}

void generate_pay_slip(permanent_employee per){                        //fun. to generate pay slips  of permanent employees
    int no;
    char fl_name[8],num[8],emp[8],c;

    cout<<"\n\nEnter the month no (1...12)  ";
    cin>>no;
    cin.clear();
    cin.ignore();
    if(no<1||no>12){
        cout<<"\n\nInvalid month number";
        return;
    }
    //system("CLS");
    cout<<":::::::::::::::::::::::::::Pay Slip for Month number "<<no<<":::::::::::::::::::\n\n ";
    per.calculate();                                                     //perform calculation
    per.displaydata();                                                   //display  data about employee
    //create a file name to store pat slip of employee by concatenating employee no. with month no. with an underscore char in between
    sprintf(num, "%d", no);
    sprintf(emp, "%d",per.emp_no);
    strcpy(fl_name,num);
    strcat(fl_name,emp);
    fl_name[strlen(num)+strlen(emp)] = '\0';
    ofstream outfile(fl_name);
    //store pay slip in file
    outfile<<":::::::::::::::::::::::::::Pay Slip for Month number "<<no<<":::::::::::::::::::\n\n ";
    outfile<<"Emp. Number             :  "<<per.emp_no<<"\n";
    outfile<<"Emp. Name               :  "<<per.emp_name<<"\n";
    outfile<<"Emp. Add                :  "<<per.emp_add<<"\n";
    outfile<<"Emp. Designation        :  "<<per.emp_desg<<"\n";
    outfile<<"Emp. Department         :  "<<per.emp_dept<<"\n";
    outfile<<"Emp. Type               :  "<<per.emp_type<<"\n";
    outfile<<"Emp. Basic              :  "<<per.emp_basic<<"\n";
    outfile<<"Dearness Allowance      :  "<<per.emp_da<<"\n";
    outfile<<"House Rent Allowance    :  "<<per.emp_hra<<"\n";
    outfile<<"Medical Allowance       :  "<<per.emp_ma<<"\n";
    outfile<<"Provident Fund          :  "<<per.emp_pf<<"\n";
    outfile<<"Professional tax        :  "<<per.ptax<<"\n";
    outfile<<"Income tax              :  "<<per.itax<<"\n";
    outfile<<"Gross Salary            :  "<<per.gross<<"\n";
    outfile<<"Net Salary              :  "<<per.net<<"\n";
    outfile.close();
}

void generate_pay_slip(contractual_employee per){                        //fun. to generate pay slips  of permanent employees
    int no;
    char fl_name[8],num[8],emp[8],c;

    cout<<"\n\nEnter the month no (1...12)  ";
    cin>>no;
    cin.clear();
    cin.ignore();
    if(no<1||no>12){
        cout<<"\n\nInvalid month number";
        return;
    }
    //system("CLS");
    cout<<":::::::::::::::::::::::::::Pay Slip for Month number "<<no<<":::::::::::::::::::\n\n ";
    per.calculate();                                                     //perform calculation
    per.displaydata();                                                   //display  data of contractual employee
    //create a file name to store pat slip of employee by concatenating employee no. with month no. with an underscore char in between
    sprintf(num, "%d", no);
    sprintf(emp, "%d",per.emp_no);
    strcpy(fl_name,num);
    strcat(fl_name,emp);
    fl_name[strlen(num)+strlen(emp)] = '\0';
    ofstream outfile(fl_name);
    //store pay slip in file
    outfile<<":::::::::::::::::::::::::::Pay Slip for Month number "<<no<<":::::::::::::::::::\n\n ";
    outfile<<"Emp. Number             :  "<<per.emp_no<<"\n";
    outfile<<"Emp. Name               :  "<<per.emp_name<<"\n";
    outfile<<"Emp. Add                :  "<<per.emp_add<<"\n";
    outfile<<"Emp. Designation        :  "<<per.emp_desg<<"\n";
    outfile<<"Emp. Department         :  "<<per.emp_dept<<"\n";
    outfile<<"Emp. Type               :  "<<per.emp_type<<"\n";
    outfile<<"Gross Salary            :  "<<per.gross<<"\n";
    outfile<<"Professional tax        :  "<<per.ptax<<"\n";
    outfile<<"Income tax              :  "<<per.itax<<"\n";
    outfile<<"Net Salary              :  "<<per.net<<"\n";
    outfile.close();
}

void compute_OT(){                                                       //func. to calculate overtime
    ifstream infile;
    permanent_employee p;
    contractual_employee c;
    int hours;
    ofstream outfile;
    infile.open("per_empf");
    outfile.open("per_payroll");
    //system("CLS");
    cout<<"\n\nComputation of Overtime Due for Permanent Employee in Progress.......";
    while(!infile.eof())
    {
        infile>>p.emp_no;
        infile.ignore(1000,'\n');
        infile.getline(p.emp_name,40);
        infile.getline(p.emp_add,80);
        infile.getline(p.emp_desg,20);
        infile.getline(p.emp_dept,20);
        infile>>p.emp_type>>p.emp_basic>>p.emp_da>>p.emp_hra>>p.emp_ma>>p.emp_pf>>p.ptax>>p.itax>>p.gross>>p.net;
        if(infile.eof())                                                 //need to check end of flag  else last employee details will be read twice
                break;
        cout<<"\nEnter the overtime hours for emp no.  "<<p.emp_no<<" : ";
        cin>>hours;
        cin.ignore();
        p.net=p.net+(hours*400);                                            //Over time rate is 400 per hour
        outfile<<p.emp_no<<"\n";
        outfile<<p.emp_name<<"\n";
        outfile<<p.emp_add<<"\n";
        outfile<<p.emp_desg<<"\n";
        outfile<<p.emp_dept<<"\n";
        outfile<<p.emp_type<<"\n";
        outfile<<p.emp_basic<<"\n";
        outfile<<p.emp_da<<"\n";
        outfile<<p.emp_hra<<"\n";
        outfile<<p.emp_ma<<"\n";
        outfile<<p.emp_pf<<"\n";
        outfile<<p.ptax<<"\n";
        outfile<<p.itax<<"\n";
        outfile<<p.gross<<"\n";
        outfile<<hours*400<<"\n";
        outfile<<p.net<<"\n";        
    }
    infile.close();
    outfile.close(); 
    cout<<"\n\nOvertime Due Computation for Permanent Employee Complet";
    infile.open("con_empf");
    outfile.open("con_payroll");
    cout<<"\n\nComputation of Overtime Due for Contractual Employee in Progress.......";
    while(!(infile.eof()))
    {
        cout<<" k  "<<infile.eof()<<endl;
        
        infile.ignore(1000,'\n');
        infile.getline(c.emp_name,40);
        infile.getline(c.emp_add,80);
        infile.getline(c.emp_desg,20);
        infile.getline(c.emp_dept,20);
        infile>>c.gross>>c.ptax>>c.itax>>c.net;
        cout<<c.emp_name<<" "<<endl;
        if(infile.eof())                                                 //need to check end of flag  else last employee details will be read twice
                break;
        cout<<"\nEnter the overtime hours for emp no.  "<<p.emp_no<<" : ";
        cin>>hours;
        cin.ignore();
        c.net=c.net+(hours*400);                                            //Over time rate is 400 per hour
        outfile<<c.emp_no<<"\n";
        outfile<<c.emp_name<<"\n";
        outfile<<c.emp_add<<"\n";
        outfile<<c.emp_desg<<"\n";
        outfile<<c.emp_dept<<"\n";
        outfile<<c.emp_type<<"\n";
        outfile<<c.gross<<"\n";
        outfile<<c.ptax<<"\n";
        outfile<<c.itax<<"\n";
        outfile<<hours*400<<"\n";
        outfile<<c.net<<"\n";         
    }
    
    infile.close();
    outfile.close();
    cout<<"\n\nOvertime Due Computation for Contractual Employee Complet";
    cin.get();
    //system("CLS");
    cout<<"\nThe Over time Dues for the employee are as following :\n\n";
    infile.open("per_payroll");
    cout.setf(ios::left,ios::adjustfield);      
    cout.width(10);
    cout<<"Emp No.";                            //display output in formatted fashion
    cout.width(40);
    cout<<"Emp. Name";
    cout.setf(ios::left,ios::adjustfield);
    cout.width(10);
    cout<<"Overtime Dues"<<"\n\n";
    while(!infile.eof()){
        infile>>p.emp_no;
        infile.ignore(1000,'\n');
        infile.getline(p.emp_name,40);
        infile.getline(p.emp_add,80);
        infile.getline(p.emp_desg,20);
        infile.getline(p.emp_dept,20);
        infile>>p.emp_type>>p.emp_basic>>p.emp_da>>p.emp_hra>>p.emp_ma>>p.emp_pf>>p.ptax>>p.itax>>p.gross>>hours>>p.net;
        if(infile.eof())                                                 //need to check end of flag  else last employee details will be read twice
                break;
        cout.setf(ios::left,ios::adjustfield);
        cout.width(10);
        cout<<p.emp_no;
        cout.setf(ios::left,ios::adjustfield);
        cout.width(40);
        cout<<p.emp_name;
        cout.width(10);
        cout<<hours<<"\n";
    }
    infile.close();
    infile.open("con_payroll");
    while(!infile.eof()){
        infile>>c.emp_no;
        infile.ignore(1000,'\n');
        infile.getline(c.emp_name,40);
        infile.getline(c.emp_add,80);
        infile.getline(c.emp_desg,20);
        infile.getline(c.emp_dept,20);
        infile>>c.emp_type>>c.gross>>c.ptax>>c.itax>>hours>>c.net;
        if(infile.eof())                                                 //need to check end of flag  else last employee details will be read twice
                break;
        cout.setf(ios::left,ios::adjustfield);
        cout.width(10);
        cout<<p.emp_no;
        cout.setf(ios::left,ios::adjustfield);
        cout.width(40);
        cout<<p.emp_name;
        cout.width(10);
        cout<<hours<<"\n";
    }
    infile.close();
}

int get_da_rate(){                                                         //fun. to retrive da rate from file
    int da;
    ifstream infile("da_file");
    infile>>da;
    infile.close();
    return da;
}

int get_hra_rate(){                                                         //fun. to retrive hra rate from file
    int hra;
    ifstream infile("hra_file");
    infile>>hra;
    infile.close();
    return hra;
}

int get_ma(){                                                         //fun. to retrive medical allowance from file
    int ma;
    ifstream infile("ma_file");
    infile>>ma;
    infile.close();
    return ma;
}

int get_ptax(){                                                         //fun. to retrive profeddional tax from file
    int ptax;
    ifstream infile("ptax_file");
    infile>>ptax;
    infile.close();
    return ptax;
}

void set_da_rate(int da){                                                         //fun. to set da rate 
    
    ofstream outfile("da_file");
    outfile<<da;
    outfile.close();
}

void set_hra_rate(int hra){                                                         //fun. to set hra rate 
    
    ofstream outfile("hra_file");
    outfile<<hra;
    outfile.close();
}

void set_ma(int ma){                                                         //fun. to set medical allowance rate 
    
    ofstream outfile("ma_file");
    outfile<<ma;
    outfile.close();
}

void set_ptax(int ptax){                                                         //fun. to set professional tax rate 
    
    ofstream outfile("ptax_file");
    outfile<<ptax;
    outfile.close();
}

int get_emp_no(){
    ifstream infile;
    infile.open("empno_fl");
    int no;
    if(!infile.fail())
    {
        infile>>no;
        no=no+1;
        infile.close();
    }
    else no =1;
    ofstream outfile("empno_fl");
    outfile<<no;
    outfile.close();
    return no;

}

int32_t main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    // #endif
    int choice ,emp_type,no;
    int da,hra,ma,ptax;
    permanent_employee per_person;
    contractual_employee con_person;
    while(1)
    {
        //system("CLS");
        cout<<"\n:::::::::::::MENU:::::::::::::::";
        cout<<"\n1. New Employee";
        cout<<"\n2. Generate Pay Slip";
        cout<<"\n3. Set Dearness Allowance rate";
        cout<<"\n4. Set HRA rate";
        cout<<"\n5. Set Professional tax";
        cout<<"\n6. Set Mesical Alloeance rate";
        cout<<"\n7. Display Details of Employee";
        cout<<"\n8. Compute Overtime Dues For Employees";
        cout<<"\n9. Exit";
        cout<<"\n\nEnter Your Choice:: ";
        cin>>choice;
        fflush(stdin);
        //system("CLS");
        switch (choice)
        {
        case 1:                                                           //Entering New employee details
            cout<<"\nEnter the employee type";
            cout<<"\n1. Permanent Employee";
            cout<<"\n2. Contractual Employee";
            cin>>emp_type;
            cin.ignore();
            switch (emp_type)
            {
            case 1:                                                       //permanent employee
                per_person.getdata();
                per_person.store_in_file();
                break;
            case 2:                                                       //Contractual Type
                con_person.getdata();
                con_person.store_in_file();
                break;
            default:
            cout<<"\n\n Wrong Type";
                break;
            }
            break;
        case 2:                                                             //Generate Pay Slip
            cout<<"\nEnter rhe employee no.: ";
            cin>>no;
            cin.ignore();
            cout<<"\nEnter the employee type:  ";
            cout<<"\n1. Permanent Employee";
            cout<<"\n2. Contractual Employee";
            cin>>emp_type;
            cin.ignore();
            switch (emp_type)
            {
            case 1:                                                       //permanent employee
                if((search(no,&per_person))==0){
                    cout<<"\n\nInvalid Employee number";
                }
                else
                {
                    generate_pay_slip(per_person);
                }
                break;
            case 2:                                                       //Contractual Type
                if((search(no,&con_person))==0){
                    cout<<"\n\nInvalid Employee number";
                }
                else
                {
                    generate_pay_slip(con_person);
                }
                break;
            default:
            cout<<"\n\n Wrong Type";
                break;
            }
            case 3:                                                       //set DA rate
            cout<<"\n\nEnter new Dearness Allowance rate:   ";
            cin>>da;
            cin.ignore();
            set_da_rate(da);
            break;
            case 4:                                                       //Set HRA rate
            cout<<"\n\nEnter new HRA rate:  ";
            cin>>hra;
            set_hra_rate(hra);
            break;
            case 5:                                                       //set Professional tax
            cout<<"\n\nEnter new Professional Tax:  ";
            cin>>ptax;
            set_ptax(ptax);
            break;
            case 6:                                                       //set Medical Allowance
            cout<<"\n\nEnter the Medical Allowance:  ";
            cin>>ma;
            set_ma(ma);
            break;
            case 7:                                                       //Search  for Eemployee
            cout<<"\n\nEnter Employee no. : ";
            cin>>no;
            cin.ignore();
            cout<<"\nEnter the employee type:  ";
            cout<<"\n1. Permanent Employee";
            cout<<"\n2. Contractual Employee";
            cin>>emp_type;
            cin.ignore();
            switch (emp_type)
            {
            case 1:                                                       //permanent employee
                if((search(no,&per_person))==0){
                    cout<<"\n\nInvalid Employee number";
                }
                else
                {
                    per_person.displaydata();
                }
                break;
            case 2:                                                       //Contractual Type
                if((search(no,&con_person))==0){
                    cout<<"\n\nInvalid Employee number";
                }
                else
                {
                    con_person.displaydata();
                }
                break;
            default:
            cout<<"\n\n Wrong Type";
                break;
            }
            break;
            case 8:                                                      //Compute Overtime Dues for employee
            compute_OT();
            break;
            case 9:                                                       //Exit System
            exit(0);
            default:
            cout<<"\n\nWrong Choice";
        }                                                                   //End of switch case for main menu
    }                                                                      // end of while loop
    return 0;
}