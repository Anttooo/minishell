#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/TestHarness.h"
#include "../testing_framework/cpputest-3.8/include/CppUTest/MemoryLeakDetectorNewMacros.h"
#include <iostream>


extern "C" {
#include "../include/command.h"
#include "../include/minishell.h"
}

extern t_data	g_data;
extern char		**environ;

void init_g_data_tokeniser() {
    // Initialize the g_data struct here, for example:
	g_data.dir.start = (char *)malloc(1024);
	getcwd(g_data.dir.start, 1024); // store the initial directory so that it can be returned before exiting
    g_data.dir.builtins = ft_strdup(ft_strjoin(g_data.dir.start, "/builtins/executables/"));
	g_data.env.paths = get_paths();
	g_data.env.vars = get_env_vars(environ);
    // ... and so on
}

TEST_GROUP(TokenizerTestGroup)
{
	void	setup() {
		init_g_data_tokeniser();
	}
};

TEST(TokenizerTestGroup, SimpleCase1)
{
  // raw input string
  g_data.cur.raw = "echo";
  // run tokenizer
  tokenize_input();
  // get result from the token struct
  t_token	*result_token = (t_token*)vec_get(&g_data.cur.vec_tokens, 0);
  char	*result = result_token->token;
  STRCMP_EQUAL("echo", result);
}

TEST(TokenizerTestGroup, SimpleCase2)
{
  // raw input string
  g_data.cur.raw = "echo hello";
  // run tokenizer
  tokenize_input();
  // token at index 0 should be 'echo'
  t_token	*result_token0 = (t_token*)vec_get(&g_data.cur.vec_tokens, 0);
  STRCMP_EQUAL("echo", result_token0->token);
  // token at index 1 should be 'hello'
  t_token	*result_token1 = (t_token*)vec_get(&g_data.cur.vec_tokens, 1); // take the token with index 1
  STRCMP_EQUAL("hello", result_token1->token);
}


IMPORT_TEST_GROUP(TokenizerTestGroup);
