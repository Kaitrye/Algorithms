#include "Rating.hpp"

int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		return -3;
	}

	Rating st;
	st.load(argv[1]);
	st.sort();
	st.print_stat();

	return 0;
}