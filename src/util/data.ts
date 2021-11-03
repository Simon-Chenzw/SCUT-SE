export class DataLine {
  [key: string]: string;
}

export class DataTable {
  readonly header: string[];
  lines: DataLine[] = [];

  constructor(header: string[] = []) {
    this.header = header;
  }

  push(row: string[]): void {
    const line = new DataLine();
    this.header.forEach((val, ind) => {
      line[val] = row[ind];
    });
    this.lines.push(line);
  }
}

export class DataBase {
  tables: { name: string; table: DataTable }[] = [];

  create(name: string, header: string[]): DataTable {
    const table = new DataTable(header);
    this.tables.push({ name, table });
    return table;
  }
}
