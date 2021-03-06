Syntax Reference
================

### The SELECT statement

    SELECT
        select_expr [, select_expr ...]
        [FROM table_references
            [WHERE predicate_expr]
            [GROUP BY {col_name | expr}, ...]
            [HAVING predicate_expr]
            [ORDER BY {col_name | expr} [ASC | DESC], ...]
            [LIMIT {[offset,] row_count | row_count OFFSET offset}]]


    table_references ::=
        table_reference [, table_reference] ...

    table_reference ::=
        table_factor
      | join_table

    table_factor:
        tbl_name [[AS] alias]
      | table_subquery [AS] alias
      | ( table_reference )

    join_table:
        table_reference [INNER | CROSS] JOIN table_factor [join_condition]
      | table_reference {LEFT|RIGHT} [OUTER] JOIN table_reference join_condition
      | table_reference NATURAL [{LEFT|RIGHT} [OUTER]] JOIN table_factor

    join_condition:
        ON conditional_expr
      | USING (column_list)


### The DRAW statement

    common_chart_options ::=
        [ TITLE 'title' ]
        [ SUBTITLE 'subtitle' ]
        [ XDOMAIN [ min, max ] [ LOGARITHMIC ] [ INVERT ] ]
        [ YDOMAIN [ min, max ] [ LOGARITHMIC ] [ INVERT ] ]
        [ ZDOMAIN [ min, max ] [ LOGARITHMIC ] [ INVERT ] ]
        [ GRID [ HORIZONTAL ] [ VERTICAL ] ]
        [ axis_definition... ]
        [ legend_definition ]

    axis_definition ::=
        AXIS { TOP | RIGHT | BOTTOM | LEFT }
            [ TITLE 'title' ]
            [ TICKS [ { INSIDE | OUTSIDE | OFF } ] [ ROTATE deg ] ]

    legend_definition ::=
        LEGEND { TOP | BOTTOM } { LEFT | RIGHT} { INSIDE | OUTSIDE }
            [ TITLE 'title' ]

    DRAW AREACHART
        [ [ WITH ]
              common_chart_options
              [ STACKED ] ]

    DRAW BARCHART
        [ [ WITH ]
              common_chart_options
              [ ORIENTATION { HORIZONTAL | VERTICAL } ]
              [ STACKED ] ]

    DRAW HEATMAP
        [ [ WITH ]
              common_chart_options ]

    DRAW HISTOGRAM
        [ [ WITH ]
              common_chart_options ]

    DRAW LINECHART
        [ [ WITH ]
              common_chart_options ]

    DRAW POINTCHART
        [ [ WITH ]
              common_chart_options ]



### The CREATE TABLE statement

    CREATE TABLE table_name
    ( column_definition, column_definition, ...)

    column_definition ::=
        column_name sql_type
      | column_name column_type [NOT NULL] [ PRIMARY KEY ]
      | column_name REPEATED column_type
      | column_name [REPEATED] RECORD ( column_definition, column_definition, ...)
      | PRIMARY KEY ( column_name [, column_name1 , column_name2, ... ] )


### The INSERT statement

    INSERT INTO table_name
      (column_name, ...) VALUES (expr, ...)
    | FROM JSON "{ ... }"


### The CREATE DATABASE statement

    CREATE DATABASE db_name


### The ALTER TABLE statement

    ALTER TABLE table_name
    alter_specification [, alter_specification, ...]

    alter_specification ::=
        ADD [COLUMN] column_definition
      | DROP [COLUMN] column_name

    column_definition ::=
        column_name [REPEATED] sql_type [NOT NULL]

