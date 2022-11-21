const db = require('../database');

const card = {
  getById: function(id, callback) {
    return db.query('select * from card where id_card=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  add: function(add_card, callback) {
    return db.query(
      'insert into card (id_owner,cardnumber,password,credit) values (?,?,?,?)',
      [add_card.id_owner, add_card.cardnumber, add_card.password,add_card.credit],
      callback
    ); // tieto lähtee arrayna
  },
  delete: function(id, callback) {
    return db.query('delete from card where id_card=?', [id], callback);
  },
  update: function(id, card, callback) {
    return db.query(
      'update card set cardnumber=?,password=?, credit=?, id_owner=? where id_card=?',
      [card.cardnumber, card.password, card.credit,card.id_owner,id],
      callback
    );
  }
};
module.exports = card;