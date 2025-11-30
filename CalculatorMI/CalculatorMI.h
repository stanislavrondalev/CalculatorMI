#pragma once

void write_data_in_file_excel(std::map<std::string, std::vector<std::vector<double>>>& m_xlsx, std::string& name, std::map<std::string, std::vector<std::string>>& map_names);

void write_data_in_text_file(std::vector<std::string>& v_txt, std::ofstream& out, std::string& name);

void convert_file_excel_in_pdf(std::string& input_name, std::string& output_name);

void build_graphics_I_from_m(std::string& body, std::vector<double>& M, Moment_of_inertia<Kernel>& MI_Kernel, std::vector<double>& I_m, Moment_of_inertia<Ball>& MI_Ball, Moment_of_inertia<Sphere>& MI_Sphere, Moment_of_inertia<Cylinder>& MI_Cylinder, Moment_of_inertia<Disk>& MI_Disk);
