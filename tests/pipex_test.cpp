// #include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
// #include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
// #include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"
// #include <iostream>


// extern "C" {
// #include "../include/pipex.h"
// }

// extern t_data	g_data;
// extern char		**environ;

// void init_g_data() {
//     // Initialize the g_data struct here, for example:
// 			// cmd_list, minimissään kaksi mutta tarvitaan useampia, voidaan tehdä testissä
// 				// structit pitää täyttää
// 			// env vars
// 			g_data.env.vars = NULL;
// 			g_data.dir.start = (char *)malloc(1024);
// 			getcwd(g_data.dir.start, 1024); // store the initial directory so that it can be returned before exiting
//     		g_data.dir.builtins = ft_strdup(ft_strjoin(g_data.dir.start, "/builtins/executables/"));
// 			g_data.env.paths = get_paths();
// 			// cmd count -> Täytetään testissä

//     // ... and so on
// }

// TEST_GROUP(PipeTestGroup)
// {
// 	void	setup() {
// 		init_g_data();
// 	}
// };

// // TEST(PipeTestGroup, FromStdToStd)
// // {
// // 	// input file
// // 	g_data.cur.input_file = NULL;
// // 	// output file
// // 	g_data.cur.output_file = NULL;
// // 	g_data.cur.cmd_count = 3;
// // 	allocate_cmd_list();
// // 	g_data.cur.cmd_list[0]->path = get_command_path("ls");
// // 	g_data.cur.cmd_list[1]->path = get_command_path("sort");
// // 	g_data.cur.cmd_list[2]->path = get_command_path("grep");
// // 	char *cmd_1 = "ls";
// // 	char *cmd_2 = "sort -r";
// // 	char *cmd_3 = "grep Make";
// // 	g_data.cur.cmd_list[0]->args = ft_split(cmd_1, ' ');
// // 	g_data.cur.cmd_list[1]->args = ft_split(cmd_2, ' ');
// // 	g_data.cur.cmd_list[2]->args = ft_split(cmd_3, ' ');

// // 	pipex();
// // }

// TEST(PipeTestGroup, FromStdToFile)
// {
// 	// input file
// 	g_data.cur.input_file = NULL;
// 	// output file
// 	g_data.cur.output_file = "temp/FromStdToFile";
// 	g_data.cur.cmd_count = 3;
// 	allocate_cmd_list();
// 	g_data.cur.cmd_list[0]->path = get_command_path("ls");
// 	g_data.cur.cmd_list[1]->path = get_command_path("sort");
// 	g_data.cur.cmd_list[2]->path = get_command_path("grep");
// 	char *cmd_1 = "ls";
// 	char *cmd_2 = "sort";
// 	char *cmd_3 = "grep b";
// 	g_data.cur.cmd_list[0]->args = ft_split(cmd_1, ' ');
// 	g_data.cur.cmd_list[1]->args = ft_split(cmd_2, ' ');
// 	g_data.cur.cmd_list[2]->args = ft_split(cmd_3, ' ');

// 	pipex();
// }

// // TEST(PipeTestGroup, FromFileToStd)
// // {
// // 	// input file
// // 	g_data.cur.input_file = "temp/FromFileToStd";
// // 	// output file
// // 	g_data.cur.output_file = NULL;
// // 	g_data.cur.cmd_count = 3;
// // 	allocate_cmd_list();
// // 	g_data.cur.cmd_list[0]->path = get_command_path("ls");
// // 	g_data.cur.cmd_list[1]->path = get_command_path("sort");
// // 	g_data.cur.cmd_list[2]->path = get_command_path("grep");
// // 	char *cmd_1 = "ls";
// // 	char *cmd_2 = "sort";
// // 	char *cmd_3 = "grep Make";
// // 	g_data.cur.cmd_list[0]->args = ft_split(cmd_1, ' ');
// // 	g_data.cur.cmd_list[1]->args = ft_split(cmd_2, ' ');
// // 	g_data.cur.cmd_list[2]->args = ft_split(cmd_3, ' ');

// // 	pipex();
// // }

// // TEST(PipeTestGroup, FromFileToFile)
// // {
// // 	// input file
// // 	g_data.cur.input_file = "temp/input1";
// // 	// output file
// // 	g_data.cur.output_file = "temp/FromFileToFile";
// // 	g_data.cur.cmd_count = 3;
// // 	allocate_cmd_list();
// // 	g_data.cur.cmd_list[0]->path = get_command_path("ls");
// // 	g_data.cur.cmd_list[1]->path = get_command_path("sort");
// // 	g_data.cur.cmd_list[2]->path = get_command_path("grep");
// // 	char *cmd_1 = "ls";
// // 	char *cmd_2 = "sort";
// // 	char *cmd_3 = "grep Make";
// // 	g_data.cur.cmd_list[0]->args = ft_split(cmd_1, ' ');
// // 	g_data.cur.cmd_list[1]->args = ft_split(cmd_2, ' ');
// // 	g_data.cur.cmd_list[2]->args = ft_split(cmd_3, ' ');

// // 	pipex();
// // }

// // TEST(PipeTestGroup, SingleStdtoStd)
// // {
// // 	g_data.cur.input_file = NULL;
// // 	g_data.cur.output_file = NULL;
// // 	g_data.cur.cmd_count = 1;
// // 	allocate_cmd_list();
// // 	g_data.cur.cmd_list[0]->path = get_command_path("cat");
// // 	char *cmd_1 = "cat temp/singletest1";
// // 	g_data.cur.cmd_list[0]->args = ft_split(cmd_1, ' ');

// // 	pipex();
// // }

// // TEST(PipeTestGroup, SingleStdtoFile)
// // {
// // 	g_data.cur.input_file = NULL;
// // 	g_data.cur.output_file = "temp/singleoutputfromstd";
// // 	g_data.cur.cmd_count = 1;
// // 	allocate_cmd_list();
// // 	g_data.cur.cmd_list[0]->path = get_command_path("cat");
// // 	char *cmd_1 = "cat temp/singletest1";
// // 	g_data.cur.cmd_list[0]->args = ft_split(cmd_1, ' ');

// // 	pipex();
// // }

// // TEST(PipeTestGroup, SingleFiletoStd)
// // {
// // 	g_data.cur.input_file = "temp/singleinput";
// // 	g_data.cur.output_file = NULL;
// // 	g_data.cur.cmd_count = 1;
// // 	allocate_cmd_list();
// // 	g_data.cur.cmd_list[0]->path = get_command_path("sort");
// // 	char *cmd_1 = "sort";
// // 	g_data.cur.cmd_list[0]->args = ft_split(cmd_1, ' ');

// // 	pipex();
// // }

// // TEST(PipeTestGroup, SingleFiletoFile)
// // {
// // 	g_data.cur.input_file = "temp/singleinput";
// // 	g_data.cur.output_file = "singleoutputfromfile";
// // 	g_data.cur.cmd_count = 1;
// // 	allocate_cmd_list();
// // 	g_data.cur.cmd_list[0]->path = get_command_path("sort");
// // 	char *cmd_1 = "sort";
// // 	g_data.cur.cmd_list[0]->args = ft_split(cmd_1, ' ');

// // 	pipex();
// // }


// IMPORT_TEST_GROUP(PipeTestGroup);
