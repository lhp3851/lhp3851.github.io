---
title: iOS之SQLite
date: 2021-04-20 21:36:02
tags:  
---

## 1、终端命令

```sql
.auth ON|OFF           Show authorizer callbacks
.backup ?DB? FILE      Backup DB (default "main") to FILE
                         Add "--append" to open using appendvfs.
.bail on|off           Stop after hitting an error.  Default OFF
.binary on|off         Turn binary output on or off.  Default OFF
.cd DIRECTORY          Change the working directory to DIRECTORY
.changes on|off        Show number of rows changed by SQL
.check GLOB            Fail if output since .testcase does not match
.clone NEWDB           Clone data into NEWDB from the existing database
.databases             List names and files of attached databases
.dbconfig ?op? ?val?   List or change sqlite3_db_config() options
.dbinfo ?DB?           Show status information about the database
.dump ?TABLE? ...      Dump the database in an SQL text format
                         If TABLE specified, only dump tables matching
                         LIKE pattern TABLE.
.echo on|off           Turn command echo on or off
.eqp on|off|full       Enable or disable automatic EXPLAIN QUERY PLAN
.excel                 Display the output of next command in a spreadsheet
.exit                  Exit this program
.expert                EXPERIMENTAL. Suggest indexes for specified queries
.fullschema ?--indent? Show schema and the content of sqlite_stat tables
.headers on|off        Turn display of headers on or off
.help                  Show this message
.import FILE TABLE     Import data from FILE into TABLE
.imposter INDEX TABLE  Create imposter table TABLE on index INDEX
.indexes ?TABLE?       Show names of all indexes
                         If TABLE specified, only show indexes for tables
                         matching LIKE pattern TABLE.
.limit ?LIMIT? ?VAL?   Display or change the value of an SQLITE_LIMIT
.lint OPTIONS          Report potential schema issues. Options:
                         fkey-indexes     Find missing foreign key indexes
.log FILE|off          Turn logging on or off.  FILE can be stderr/stdout
.mode MODE ?TABLE?     Set output mode where MODE is one of:
                         ascii    Columns/rows delimited by 0x1F and 0x1E
                         csv      Comma-separated values
                         column   Left-aligned columns.  (See .width)
                         html     HTML <table> code
                         insert   SQL insert statements for TABLE
                         line     One value per line
                         list     Values delimited by "|"
                         quote    Escape answers as for SQL
                         tabs     Tab-separated values
                         tcl      TCL list elements
.nullvalue STRING      Use STRING in place of NULL values
.once (-e|-x|FILE)     Output for the next SQL command only to FILE
                         or invoke system text editor (-e) or spreadsheet (-x)
                         on the output.
.open ?OPTIONS? ?FILE? Close existing database and reopen FILE
                         The --new option starts with an empty file
                         Other options: --readonly --append --zip
.output ?FILE?         Send output to FILE or stdout
.print STRING...       Print literal STRING
.prompt MAIN CONTINUE  Replace the standard prompts
.quit                  Exit this program
.read FILENAME         Execute SQL in FILENAME
.restore ?DB? FILE     Restore content of DB (default "main") from FILE
.save FILE             Write in-memory database into FILE
.scanstats on|off      Turn sqlite3_stmt_scanstatus() metrics on or off
.schema ?PATTERN?      Show the CREATE statements matching PATTERN
                          Add --indent for pretty-printing
.selftest ?--init?     Run tests defined in the SELFTEST table
.separator COL ?ROW?   Change the column separator and optionally the row
                         separator for both the output mode and .import
.session CMD ...       Create or control sessions
.sha3sum ?OPTIONS...?  Compute a SHA3 hash of database content
.shell CMD ARGS...     Run CMD ARGS... in a system shell
.show                  Show the current values for various settings
.stats ?on|off?        Show stats or turn stats on or off
.system CMD ARGS...    Run CMD ARGS... in a system shell
.tables ?TABLE?        List names of tables
                         If TABLE specified, only list tables matching
                         LIKE pattern TABLE.
.testcase NAME         Begin redirecting output to 'testcase-out.txt'
.timeout MS            Try opening locked tables for MS milliseconds
.timer on|off          Turn SQL timer on or off
.trace FILE|off        Output each SQL statement as it is run
.vfsinfo ?AUX?         Information about the top-level VFS
.vfslist               List all available VFSes
.vfsname ?AUX?         Print the name of the VFS stack
.width NUM1 NUM2 ...   Set column widths for "column" mode
                         Negative values right-justify

```

## 2、程序

SQLite 语句

所有的 SQLite 语句可以以任何关键字开始，如 SELECT、INSERT、UPDATE、DELETE、ALTER、DROP 等，所有的语句以分号（;）结束。

2.1 SQLite ANALYZE 语句：

``` sql
ANALYZE;
or
ANALYZE database_name;
or
ANALYZE database_name.table_name;
```

2.2 SQLite AND/OR 子句：

``` sql
SELECT column1, column2....columnN
FROM   table_name
WHERE  CONDITION-1 {AND|OR} CONDITION-2;
```

2.3 SQLite ALTER TABLE 语句：

``` sql
ALTER TABLE table_name ADD COLUMN column_def...;
```

2.4 SQLite ALTER TABLE 语句（Rename）：

``` sql
ALTER TABLE table_name RENAME TO new_table_name;
```

2.5 SQLite ATTACH DATABASE 语句：

``` sql
ATTACH DATABASE 'DatabaseName' As 'Alias-Name';
```

2.6 SQLite BEGIN TRANSACTION 语句：

``` sql
BEGIN;
or
BEGIN EXCLUSIVE TRANSACTION;
```

2.7 SQLite BETWEEN 子句：

``` sql
SELECT column1, column2....columnN
FROM   table_name
WHERE  column_name BETWEEN val-1 AND val-2;
```

2.8 SQLite COMMIT 语句：

``` sql
COMMIT;
```

2.9 SQLite CREATE INDEX 语句：

``` sql
CREATE INDEX index_name
ON table_name ( column_name COLLATE NOCASE );
```

2.10 SQLite CREATE UNIQUE INDEX 语句：

``` sql
CREATE UNIQUE INDEX index_name
ON table_name ( column1, column2,...columnN);
```

2.11 SQLite CREATE TABLE 语句：

``` sql
CREATE TABLE table_name(
   column1 datatype,
   column2 datatype,
   column3 datatype,
   .....
   columnN datatype,
   PRIMARY KEY( one or more columns )
);
```

2.12 SQLite CREATE TRIGGER 语句：

``` sql
CREATE TRIGGER database_name.trigger_name
BEFORE INSERT ON table_name FOR EACH ROW
BEGIN
   stmt1;
   stmt2;
   ....
END;
```

2.13 SQLite CREATE VIEW 语句：

``` sql
CREATE VIEW database_name.view_name  AS
SELECT statement....;
```

2.14 SQLite CREATE VIRTUAL TABLE 语句：

``` sql
CREATE VIRTUAL TABLE database_name.table_name USING weblog( access.log );
or
CREATE VIRTUAL TABLE database_name.table_name USING fts3( );
```

2.15 SQLite COMMIT TRANSACTION 语句：

``` sql
COMMIT;
```

2.16 SQLite COUNT 子句：

``` sql
SELECT COUNT(column_name)
FROM   table_name
WHERE  CONDITION;
```

2.17 SQLite DELETE 语句：

``` sql
DELETE FROM table_name
WHERE  {CONDITION};
```

2.18 SQLite DETACH DATABASE 语句：

``` sql
DETACH DATABASE 'Alias-Name';
```

2.19 SQLite DISTINCT 子句：

``` sql
SELECT DISTINCT column1, column2....columnN
FROM   table_name;
```

2.20 SQLite DROP INDEX 语句：

``` sql
DROP INDEX database_name.index_name;
```

2.21 SQLite DROP TABLE 语句：

``` sql
DROP TABLE database_name.table_name;
```

2.22 SQLite DROP VIEW 语句：

``` sql
DROP VIEW view_name;
```

2.23 SQLite DROP TRIGGER 语句：

``` sql
DROP TRIGGER trigger_name
```

2.24 SQLite EXISTS 子句：

``` sql
SELECT column1, column2....columnN
FROM   table_name
WHERE  column_name EXISTS (SELECT * FROM   table_name );
```

2.25 SQLite EXPLAIN 语句：

``` sql
EXPLAIN INSERT statement...;
or
EXPLAIN QUERY PLAN SELECT statement...;
```

2.26 SQLite GLOB 子句：

``` sql
SELECT column1, column2....columnN
FROM   table_name
WHERE  column_name GLOB { PATTERN };
```

2.27 SQLite GROUP BY 子句：

``` sql
SELECT SUM(column_name)
FROM   table_name
WHERE  CONDITION
GROUP BY column_name;
```

2.28 SQLite HAVING 子句：

``` sql
SELECT SUM(column_name)
FROM   table_name
WHERE  CONDITION
GROUP BY column_name
HAVING (arithematic function condition);
```

2.29 SQLite INSERT INTO 语句：

``` sql
INSERT INTO table_name( column1, column2....columnN)
VALUES ( value1, value2....valueN);
```

2.30 SQLite IN 子句：

``` sql
SELECT column1, column2....columnN
FROM   table_name
WHERE  column_name IN (val-1, val-2,...val-N);
```

2.31 SQLite Like 子句：

``` sql
SELECT column1, column2....columnN
FROM   table_name
WHERE  column_name LIKE { PATTERN };
```

2.32 SQLite NOT IN 子句：

``` sql
SELECT column1, column2....columnN
FROM   table_name
WHERE  column_name NOT IN (val-1, val-2,...val-N);
```

2.33 SQLite ORDER BY 子句：

``` sql
SELECT column1, column2....columnN
FROM   table_name
WHERE  CONDITION
ORDER BY column_name {ASC|DESC};
```

2.34 SQLite PRAGMA 语句：

``` sql
PRAGMA pragma_name;

For example:
PRAGMA page_size;
PRAGMA cache_size = 1024;
PRAGMA table_info(table_name);
```

2.35 SQLite RELEASE SAVEPOINT 语句：

``` sql
RELEASE savepoint_name;
```

2.36 SQLite REINDEX 语句：

``` sql
REINDEX collation_name;
REINDEX database_name.index_name;
REINDEX database_name.table_name;
```

2.37 SQLite ROLLBACK 语句：

``` sql
ROLLBACK;
or
ROLLBACK TO SAVEPOINT savepoint_name;
```

2.38 SQLite SAVEPOINT 语句：

``` sql
SAVEPOINT savepoint_name;
```

2.39 SQLite SELECT 语句：

``` sql
SELECT column1, column2....columnN
FROM   table_name;
```

2.40 SQLite UPDATE 语句：

``` sql
UPDATE table_name
SET column1 = value1, column2 = value2....columnN=valueN
[ WHERE  CONDITION ];
```

2.41 SQLite VACUUM 语句：

``` sql
VACUUM;
```

2.42 SQLite WHERE 子句：

``` sql
SELECT column1, column2....columnN
FROM   table_name
WHERE  CONDITION;
```

## 3、常见专有名词

事务
游标
触发器
存储过程
回滚
约束
索引
视图

## 4、常用操作

数据同步
导入、导出
CRUD (Create/Retrieve/Update/Delete)

## 5、建表原则

数据范式

## 6、事务特性

ACID

## 7、数据库

常见数据库：SQLite、MySQL、SQLServer、Oracle、MOngoDB

7.1 分类：
    关系型：Oracle和MySQL
    非关系型：NoSQL(NoSQL = Not Only SQL )
（1）键值存储数据库（key-value）

键值数据库就类似传统语言中使用的哈希表。可以通过key来添加、查询或者删除数据库，因为使用key主键访问，所以会获得很高的性能及扩展性。

键值数据库主要使用一个哈希表，这个表中有一个特定的键和一个指针指向特定的数据。Key/value模型对于IT系统来说的优势在于简单、易部署、高并发。

典型产品：Memcached、Redis、MemcacheDB

（2）列存储（Column-oriented）数据库

列存储数据库将数据存储在列族中，一个列族存储经常被一起查询的相关数据，比如人类，我们经常会查询某个人的姓名和年龄，而不是薪资。这种情况下姓名和年龄会被放到一个列族中，薪资会被放到另一个列族中。

这种数据库通常用来应对分布式存储海量数据。

典型产品：Cassandra、HBase

（3）面向文档（Document-Oriented）数据库

文档型数据库的灵感是来自于Lotus Notes办公软件，而且它同第一种键值数据库类似。该类型的数据模型是版本化的文档，半结构化的文档以特定的格式存储，比如JSON。文档型数据库可以看作是键值数据库的升级版，允许之间嵌套键值。而且文档型数据库比键值数据库的查询效率更高。

面向文档数据库会将数据以文档形式存储。每个文档都是自包含的数据单元，是一系列数据项的集合。每个数据项都有一个名词与对应值，值既可以是简单的数据类型，如字符串、数字和日期等；也可以是复杂的类型，如有序列表和关联对象。数据存储的最小单位是文档，同一个表中存储的文档属性可以是不同的，数据可以使用XML、JSON或JSONB等多种形式存储。

典型产品：MongoDB、CouchDB

（4）图形数据库

图形数据库允许我们将数据以图的方式存储。实体会被作为顶点，而实体之间的关系则会被作为边。比如我们有三个实体，Steve Jobs、Apple和Next，则会有两个“Founded by”的边将Apple和Next连接到Steve Jobs。

典型产品：Neo4J、InforGrid

7.2 数据库引擎：数据库引擎是用于存储、处理和保护数据的核心服务。
MYSQL支持三个引擎：ISAM、MYISAM和HEAP。另外两种类型INNODB和BERKLEY（BDB），也常常可以使用。

你能用的数据库引擎取决于mysql在安装的时候是如何被编译的。要添加一个新的引擎，就必须重新编译MYSQL。在缺省情况下，MYSQL支持三个引擎：ISAM、MYISAM和HEAP。另外两种类型INNODB和BERKLEY（BDB），也常常可以使用。

* ISAM
  
>ISAM是一个定义明确且历经时间考验的数据表格管理方法，它在设计之时就考虑到数据库被查询的次数要远大于更新的次数。因此，ISAM执行读取操作的速度很快，而且不占用大量的内存和存储资源。ISAM的两个主要不足之处在于，它不支持事务处理，也不能够容错：如果你的硬盘崩溃了，那么数据文件就无法恢复了。如果你正在把ISAM用在关键任务应用程序里，那就必须经常备份你所有的实时数据，通过其复制特性，MYSQL能够支持这样的备份应用程序。

* MYISAM
  
>MYISAM是MYSQL的ISAM扩展格式和缺省的数据库引擎。除了提供ISAM里所没有的索引和字段管理的大量功能，MYISAM还使用一种表格锁定的机制，来优化多个并发的读写操作。其代价是你需要经常运行OPTIMIZE TABLE命令，来恢复被更新机制所浪费的空间。MYISAM还有一些有用的扩展，例如用来修复数据库文件的MYISAMCHK工具和用来恢复浪费空间的MYISAMPACK工具。
MYISAM强调了快速读取操作，这可能就是为什么MYSQL受到了WEB开发如此青睐的主要原因：在WEB开发中你所进行的大量数据操作都是读取操作。所以，大多数虚拟主机提供商和INTERNET平台提供商只允许使用MYISAM格式。

* HEAP

>HEAP允许只驻留在内存里的临时表格。驻留在内存里让HEAP要比ISAM和MYISAM都快，但是它所管理的数据是不稳定的，而且如果在关机之前没有进行保存，那么所有的数据都会丢失。在数据行被删除的时候，HEAP也不会浪费大量的空间。HEAP表格在你需要使用SELECT表达式来选择和操控数据的时候非常有用。要记住，在用完表格之后就删除表格。

* INNODB和BERKLEYDB

>INNODB和BERKLEYDB（BDB）数据库引擎都是造就MYSQL灵活性的技术的直接产品，这项技术就是MYSQL++ API。在使用MYSQL的时候，你所面对的每一个挑战几乎都源于ISAM和MYISAM数据库引擎不支持事务处理也不支持外来键。尽管要比ISAM和MYISAM引擎慢很多，但是INNODB和BDB包括了对事务处理和外来键的支持，这两点都是前两个引擎所没有的。如前所述，如果你的设计需要这些特性中的一者或者两者，那你就要被迫使用后两个引擎中的一个了。
