#define SQL_HOST				"127.0.0.1"
#define SQL_USER				"db_user"
#define SQL_DB					"db_name"
#define SQL_PASSWORD			"db_password"

stock mysql_query_format(format_query[], va_args<>)
{
	new query[1024];

	va_format(query, sizeof(query), format_query, va_start<1>);
	mysql_query(query);

	return 1;
}