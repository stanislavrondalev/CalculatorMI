// CalculatorMI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Moment_of_inertia.h"
#include "MI_Kernel.h"
#include "string"
#include "vector"
#include "map"
#include "fstream"
#include "Spire.Xls.o.h"
#include "matplotlibcpp.h"
#include "math.h"
#include "CalculatorMI.h"
using namespace std;
using namespace Spire::Xls;
using namespace matplotlibcpp;

wstring to_wstring(string s) {
    wstring ws(s.begin(), s.end());
    return ws;
}

void write_data_in_file_excel(std::map<std::string, std::vector<std::vector<double>>>& m_xlsx, std::string& name, std::map<std::string, std::vector<std::string>>& map_names)
{
    if (!m_xlsx.empty()) {
        wstring wname = to_wstring(name);
        wstring outputFile = wname + L".xlsx";
        intrusive_ptr<Workbook> workbook = new Workbook();
        intrusive_ptr<Worksheet> sheet = dynamic_pointer_cast<Worksheet>(workbook->GetWorksheets()->Get(0));

        int i = 1, j = 1;
        for (const auto& elem : m_xlsx) {
            wstring body = to_wstring(elem.first);
            sheet->GetRange(i, j + 1)->SetText(body.c_str());

            vector<string> map_names_body = map_names[elem.first];
            for (int s = 0; s < map_names_body.size(); s++) {
                sheet->GetRange(i + 1, j + s)->SetText(to_wstring(map_names_body[s]).c_str());
            }

            for (int k{}; k < elem.second.size(); k++) {
                for (int s{}; s < elem.second[0].size(); s++) {
                    sheet->GetRange(i + 2 + k, j + s)->SetText(to_wstring(to_string(elem.second[k][s])).c_str());
                }
            }

            j = j + elem.second[0].size() + 1;
        }

        sheet->GetAllocatedRange()->AutoFitColumns();

        intrusive_ptr <CellStyle> style = dynamic_pointer_cast<CellStyle>(workbook->GetStyles()->Add(L"newStyle"));
        style->GetFont()->SetIsBold(true);
        sheet->GetRange(1, 1, 1, j)->SetStyle(style);
        sheet->GetRange(2, 1, 2, j)->SetStyle(style);

        workbook->SaveToFile(outputFile.c_str(), ExcelVersion::Version2016);
        workbook->Dispose();
    }
    else {
        cout << "Нет данных !" << endl;
    }
}

void write_data_in_text_file(std::vector<std::string>& v_txt, std::ofstream& out, std::string& name)
{
    if (!v_txt.empty()) {
        out.open(name + ".txt");
        for (string str : v_txt) {
            out << str << endl;
        }
        out.close();
    }
    else {
        cout << "Нет данных !" << endl;
    }
}

void convert_file_excel_in_pdf(std::string& input_name, std::string& output_name)
{
    //Specify input file path
    wstring inputFilePath = to_wstring(input_name) + L".xlsx";

    //Specify output file path and name
    wstring outputFile = to_wstring(output_name) + L".pdf";

    //Create a Workbook object
    Workbook* workbook = new Workbook();

    //Load the source Excel file
    workbook->LoadFromFile(inputFilePath.c_str());

    //Set worksheets to fit to page when converting
    workbook->GetConverterSetting()->SetSheetFitToPage(true);

    //Save to PDF
    workbook->SaveToFile(outputFile.c_str(), FileFormat::PDF);
    workbook->Dispose();
}

void build_graphics_I_from_m(std::vector<double>& M)
{
    string body;

    Moment_of_inertia<Kernel> MI_Kernel;
    Moment_of_inertia<Ball> MI_Ball;
    Moment_of_inertia<Sphere> MI_Sphere;
    Moment_of_inertia<Cylinder> MI_Cylinder;
    Moment_of_inertia<Disk> MI_Disk;

    vector<double> I_m;

    while (true) {
        cout << "Вид физического тела: ";
        cin >> body;

        if (body == "1") {
            double Lg;
            cout << "Kernel:" << endl;

            while (true) {
                cout << "L = "; cin >> Lg;
                if (valid_input(cin)) break;
            }

            for (double mi : M) {
                MI_Kernel.set_data(Kernel(mi, Lg));
                I_m.push_back(MI_Kernel.get_I());
            }

            plot(M, I_m);
            named_plot("Kernel, L = " + to_string(Lg), M, I_m);
            I_m.clear();
        }

        if (body == "2") {
            double Rg;
            cout << "Ball:" << endl;

            while (true) {
                cout << "R = "; cin >> Rg;
                if (valid_input(cin)) break;
            }

            for (double mi : M) {
                MI_Ball.set_data(Ball(mi, Rg));
                I_m.push_back(MI_Ball.get_I());
            }

            plot(M, I_m);
            named_plot("Ball, R = " + to_string(Rg), M, I_m);
            I_m.clear();
        }

        if (body == "3") {
            double Rg;
            cout << "Sphere:" << endl;

            while (true) {
                cout << "R = "; cin >> Rg;
                if (valid_input(cin)) break;
            }

            for (double mi : M) {
                MI_Sphere.set_data(Sphere(mi, Rg));
                I_m.push_back(MI_Sphere.get_I());
            }

            plot(M, I_m);
            named_plot("Sphere, R = " + to_string(Rg), M, I_m);
            I_m.clear();
        }

        if (body == "4") {
            double Rg;
            cout << "Cylinder:" << endl;

            while (true) {
                cout << "R = "; cin >> Rg;
                if (valid_input(cin)) break;
            }

            for (double mi : M) {
                MI_Cylinder.set_data(Cylinder(mi, Rg));
                I_m.push_back(MI_Cylinder.get_I());
            }

            plot(M, I_m);
            named_plot("Cylinder, R = " + to_string(Rg), M, I_m);
            I_m.clear();
        }

        if (body == "5") {
            double Rg;
            cout << "Disk:" << endl;

            while (true) {
                cout << "R = "; cin >> Rg;
                if (valid_input(cin)) break;
            }

            for (double mi : M) {
                MI_Disk.set_data(Disk(mi, Rg));
                I_m.push_back(MI_Disk.get_I());
            }

            plot(M, I_m);
            named_plot("Disk, R = " + to_string(Rg), M, I_m);
            I_m.clear();
        }

        if (body == "-1") {
            xlabel("m");
            ylabel("I(m)");
            title("Graphics I(m)");
            legend();
            grid(true);
            show();

            break;
        }
    }
}

void build_graphics_I_from_R_or_L(std::vector<double>& RL)
{
    string body;

    Moment_of_inertia<Kernel> MI_Kernel;
    Moment_of_inertia<Ball> MI_Ball;
    Moment_of_inertia<Sphere> MI_Sphere;
    Moment_of_inertia<Cylinder> MI_Cylinder;
    Moment_of_inertia<Disk> MI_Disk;

    vector<double> I_RL;

    while (true) {
        cout << "Вид физического тела: ";
        cin >> body;

        if (body == "1") {
            double mg;
            cout << "Kernel:" << endl;

            while (true) {
                cout << "m = "; cin >> mg;
                if (valid_input(cin)) break;
            }

            for (double Li : RL) {
                MI_Kernel.set_data(Kernel(mg, Li));
                I_RL.push_back(MI_Kernel.get_I());
            }

            plot(RL, I_RL);
            named_plot("Kernel, m = " + to_string(mg), RL, I_RL);
            I_RL.clear();
        }

        if (body == "2") {
            double mg;
            cout << "Ball:" << endl;

            while (true) {
                cout << "m = "; cin >> mg;
                if (valid_input(cin)) break;
            }

            for (double Ri : RL) {
                MI_Ball.set_data(Ball(mg, Ri));
                I_RL.push_back(MI_Ball.get_I());
            }

            plot(RL, I_RL);
            named_plot("Ball, m = " + to_string(mg), RL, I_RL);
            I_RL.clear();
        }

        if (body == "3") {
            double mg;
            cout << "Sphere:" << endl;

            while (true) {
                cout << "m = "; cin >> mg;
                if (valid_input(cin)) break;
            }

            for (double Ri : RL) {
                MI_Sphere.set_data(Sphere(mg, Ri));
                I_RL.push_back(MI_Sphere.get_I());
            }

            plot(RL, I_RL);
            named_plot("Sphere, m = " + to_string(mg), RL, I_RL);
            I_RL.clear();
        }

        if (body == "4") {
            double mg;
            cout << "Cylinder:" << endl;

            while (true) {
                cout << "m = "; cin >> mg;
                if (valid_input(cin)) break;
            }

            for (double Ri : RL) {
                MI_Cylinder.set_data(Cylinder(mg, Ri));
                I_RL.push_back(MI_Cylinder.get_I());
            }

            plot(RL, I_RL);
            named_plot("Cylinder, m = " + to_string(mg), RL, I_RL);
            I_RL.clear();
        }

        if (body == "5") {
            double mg;
            cout << "Disk:" << endl;

            while (true) {
                cout << "m = "; cin >> mg;
                if (valid_input(cin)) break;
            }

            for (double Ri : RL) {
                MI_Disk.set_data(Disk(mg, Ri));
                I_RL.push_back(MI_Disk.get_I());
            }

            plot(RL, I_RL);
            named_plot("Disk, m = " + to_string(mg), RL, I_RL);
            I_RL.clear();
        }

        if (body == "-1") {
            xlabel("R");
            ylabel("I(R)");
            title("Graphics I(R)");
            legend();
            grid(true);
            show();

            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Moment_of_inertia<Kernel> MI_Kernel;
    Moment_of_inertia<Ball> MI_Ball;
    Moment_of_inertia<Sphere> MI_Sphere;
    Moment_of_inertia<Cylinder> MI_Cylinder;
    Moment_of_inertia<Disk> MI_Disk;
    Kernel kernel;
    Ball ball;
    Cylinder cylinder;
    Sphere sphere;
    Disk disk;

    cout << "Инструкция по вводу. В начале работы программы введите одну из цифр: 1 - преобразовать файл Excel\n\
в файл.pdf, 2 - запустить калькулятор, 3 - построить графики зависимостей моментов инерций заданных тел от их масс\n\
при заданных коэффициентах, 4 - построить графики зависимостей моментов инерций заданных тел от их радиусов (длин)\n\
при постоянных массах, 5 - завершить программу. При выборе 1: далее введите название файла, который надо\n\
конвертировать в pdf, потом название будущего pdf файла.\n\
Указания при выборе 3. \n\
      Сначала надо ввести концы отрезка, на котором будут строится графики и шаг разбиения отрезка. Потом надо ввести\n\
вид физического тела, для этого надо ввести одну из цифр: 1 - kernel, 2 - ball, 3 - sphere, 4 - cylinder,\n\
5 - disk - виды тел, для которых надо построить график; -1 - завершить ввод. Далее надо ввести значения радиуса\n\
или длины в зависимости от вида тела (для получения коэффициента). \n\
Указания при выборе 4. \n\
      Аналогично указаниям при выборе 3.\n\
Указания при выборе 2. \n\
      Там, где надо ввести вид физического тела, введите одну из цифр: 1 - kernel, 2 - ball,\n\
3 - sphere, 4 - cylinder, 5 - disk - виды тел, для которых надо определить момент инерции; -1 - завершить ввод.\n\
После завершения ввода будет предложение сохранить все введённые и полученные данные тел в файл.\n\
Введите 1 - сохранить данные в файл, что-нибудь другое, если нет. Если 1, далее введите название файла.\n\
Потом введите 1, если сохранить данные в текстовый файл, 2 - в файл Excel. Далее будет предложение продолжить\n\
ввод. Введите 1 - ввод продолжится, что-нибудь другое - выйти из калькулятора." << endl;

    string body;
    string answer;
    vector<string> v_txt;
    map<string, vector<string>> map_names;
    map<string, vector<vector<double>>> m_xlsx;
    ofstream out;

    while (true) {
        cout << "Введите номер действия: "; cin >> answer;
        if (answer == "1") {
            string input_name;
            cout << "Название файла Excel: "; cin >> input_name;

            string output_name;
            cout << "Название будущего файла pdf: "; cin >> output_name;

            convert_file_excel_in_pdf(input_name, output_name);
        }

        if ((answer == "3") || (answer == "4")) {
            
            double mR0, mR1;
            cout << "Концы отрезка:" << endl;
            
            while (true) {
                if (answer == "3") {
                    cout << "m0 = "; cin >> mR0;
                }
                if (answer == "4") {
                    cout << "R0 = "; cin >> mR0;
                }

                if (valid_input(cin)) break;
            }

            while (true) {
                if (answer == "3") {
                    cout << "m1 = "; cin >> mR1;
                }
                if (answer == "4") {
                    cout << "R1 = "; cin >> mR1;
                }

                if (valid_input(cin)) break;
            }

            double h;
            while (true) {
                cout << "Шаг разбиения отрезка h: "; cin >> h;
                if (valid_input(cin)) break;
            }

            vector<double> MR;
            for (double mRi = mR0; (mRi < mR1) || (fabs(mR1 - mRi) < 0.000001); mRi += h) {
                MR.push_back(mRi);
            }

            if (answer == "3") {
                build_graphics_I_from_m(MR);
            }
            if (answer == "4") {
                build_graphics_I_from_R_or_L(MR);
            }
        }

        if (answer == "5") {
            break;
        }

        if (answer == "2") {
            while (true) {
                while (true) {
                    cout << "Вид физического тела: ";
                    cin >> body;

                    if (body == "1") {
                        cout << "Kernel:" << endl;
                        cin >> kernel;
                        MI_Kernel.set_data(kernel);

                        double m = kernel.get_data()[0];
                        double L = kernel.get_data()[1];
                        double I = MI_Kernel.get_I();

                        cout << "I = " << I << endl;
                        v_txt.push_back("Kernel: m = " + to_string(kernel.get_data()[0]) + ", L = " + to_string(kernel.get_data()[1]) + ", I = " + to_string(I));

                        map_names["Kernel"] = { "m", "L", "I" };
                        if (m_xlsx.count("Kernel")) {
                            m_xlsx["Kernel"].push_back({ m, L, I });
                        }
                        else {
                            m_xlsx["Kernel"] = { {m, L, I} };
                        }
                    }

                    if (body == "2") {
                        cout << "Ball:" << endl;
                        cin >> ball;
                        MI_Ball.set_data(ball);

                        double m = ball.get_data()[0];
                        double R = ball.get_data()[1];
                        double I = MI_Ball.get_I();

                        cout << "I = " << I << endl;
                        v_txt.push_back("Ball: m = " + to_string(ball.get_data()[0]) + ", R = " + to_string(ball.get_data()[1]) + ", I = " + to_string(I));

                        map_names["Ball"] = { "m", "R", "I" };
                        if (m_xlsx.count("Ball")) {
                            m_xlsx["Ball"].push_back({ m, R, I });
                        }
                        else {
                            m_xlsx["Ball"] = { {m, R, I} };
                        }
                    }

                    if (body == "3") {
                        cout << "Sphere:" << endl;
                        cin >> sphere;
                        MI_Sphere.set_data(sphere);

                        double m = sphere.get_data()[0];
                        double R = sphere.get_data()[1];
                        double I = MI_Sphere.get_I();

                        cout << "I = " << I << endl;
                        v_txt.push_back("Sphere: m = " + to_string(sphere.get_data()[0]) + ", R = " + to_string(sphere.get_data()[1]) + ", I = " + to_string(I));

                        map_names["Sphere"] = { "m", "R", "I" };
                        if (m_xlsx.count("Sphere")) {
                            m_xlsx["Sphere"].push_back({ m, R, I });
                        }
                        else {
                            m_xlsx["Sphere"] = { {m, R, I} };
                        }
                    }

                    if (body == "4") {
                        cout << "Cylinder:" << endl;
                        cin >> cylinder;
                        MI_Cylinder.set_data(cylinder);

                        double m = cylinder.get_data()[0];
                        double R = cylinder.get_data()[1];
                        double I = MI_Cylinder.get_I();

                        cout << "I = " << I << endl;
                        v_txt.push_back("Cylinder: m = " + to_string(cylinder.get_data()[0]) + ", R = " + to_string(cylinder.get_data()[1]) + ", I = " + to_string(I));

                        map_names["Cylinder"] = { "m", "R", "I" };
                        if (m_xlsx.count("Cylinder")) {
                            m_xlsx["Cylinder"].push_back({ m, R, I });
                        }
                        else {
                            m_xlsx["Cylinder"] = { {m, R, I} };
                        }
                    }

                    if (body == "5") {
                        cout << "Disk:" << endl;
                        cin >> disk;
                        MI_Disk.set_data(disk);

                        double m = disk.get_data()[0];
                        double R = disk.get_data()[1];
                        double I = MI_Disk.get_I();

                        cout << "I = " << I << endl;
                        v_txt.push_back("Disk: m = " + to_string(disk.get_data()[0]) + ", R = " + to_string(disk.get_data()[1]) + ", I = " + to_string(I));

                        map_names["Disk"] = { "m", "R", "I" };
                        if (m_xlsx.count("Disk")) {
                            m_xlsx["Disk"].push_back({ m, R, I });
                        }
                        else {
                            m_xlsx["Disk"] = { {m, R, I} };
                        }
                    }

                    if (body == "-1") break;
                }

                cout << "Записать данные в файл ?" << endl;
                cout << "Ответ: "; cin >> answer;

                if (answer == "1") {
                    string name;
                    cout << "Название файла: "; cin >> name;
                    

                    while (true) {
                        cout << "Формат файла: "; cin >> answer;
                        if (answer == "1") {
                            write_data_in_text_file(v_txt, out, name);
                            break;
                        }

                        if (answer == "2") {
                            write_data_in_file_excel(m_xlsx, name, map_names);
                            break;
                        }
                    }

                }
                v_txt.clear();
                m_xlsx.clear();
                map_names.clear();

                cout << "Продолжить ввод ?" << endl;
                cout << "Ответ: "; cin >> answer;
                if (answer != "1") {
                    break;
                }
            }
        }
    }
    
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
