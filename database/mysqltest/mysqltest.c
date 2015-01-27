#include<stdlib.h>
#include<stdio.h>
#include "/usr/include/mysql/mysql.h"

int main(int argc, char *argv[])
{
	MYSQL *mysql;
	MYSQL_RES 	*result;
	MYSQL_ROW	row;
	char operation[300];
	
	/* init && connect to the database */
	mysql = mysql_init((MYSQL *) 0);
	if (mysql == NULL) {
		printf("can not initialize mysql!\n");
		return 1;
	}

	if (!mysql_real_connect(mysql, "10.48.229.48", "root",
		"sat@baidu.com", "books", 3306, NULL, 0)) {
		printf("failed to connect to the database: books !\n");
		return 1;
	}	
	
	/* query */
	if (mysql_select_db(mysql, "books")) {
		printf("failed to select the database: books\n");
		return 1;
	}
	if (mysql_query(mysql, "select * from books")) {
		printf("query failed, err info %d: %s\n", 
					mysql_errno(mysql), mysql_error(mysql));
	} else {
		result = mysql_store_result(mysql);
		while (row = mysql_fetch_row(result))
			//printf("%d -%d -%d - %d\n", *row[0], *((int *) row[0]), atoi(row[0]), atoi((char *) row[0]));
			printf("%d - %s - %d - %s - %s - %s\n",atoi((char *) row[0]), row[1], atoi((char *) row[2]), row[3],
					row[4], row[5]);
		mysql_free_result(result);
	}
/*
	
	sprintf(operation,"replace into books(bookname, author_id, isbn, description)" \
				" values ('TCP/IP Illustrated', 4, 'fd456', 'knowedge about network')");
	if (!mysql_query(mysql, operation))
		printf("insert successfully!\n");
*/
	mysql_close(mysql);
	return 0;
}
