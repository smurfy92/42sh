#include <sys/socket.h>

int		main(int argc, char **argv)
{
	int id;

    id = socket("localhost", PF_INET, SOCK_STREAM);
    printf("id -> %d\n", id);
	return (0);
}