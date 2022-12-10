const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'group_2',
  password: 'pass',
  database: 'group_2'
});
module.exports = connection;