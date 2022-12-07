const db = require('../database');
const bcrypt = require('bcryptjs');
const { response } = require('express');

const saltRounds=10;

const card = {
  debitwithdraw: function(withdraw, callback) { 
    return db.query(
      'call debit_withdraw(?,?)',
      [withdraw.id_card, withdraw.amount],
      callback);
  },
  creditwithdraw: function(withdraw, callback) { 
    return db.query(
      'call credit_withdraw(?,?)',
      [withdraw.id_card, withdraw.amount],
      callback);
  },
  getcardid: function(get_cardid, callback) {
    return db.query(
      'select id_card from card where cardnumber = ?',
      [get_cardid.cardnumber],
      callback);
    }, 
    getcardcred: function(get_cardcred, callback) {
      return db.query(
        'select credit from card where id_card = ?',
        [get_cardcred.id_card],
        callback);
      },
      update: function(id, card, callback) {  // UPDATE TÄRKEÄ SALASANAN KRYPTAUKSEEN MUUTEN VOI LISÄTÄ SQL
        bcrypt.hash(card.password, saltRounds, function(err, hash){
        return db.query(
          'update card set cardnumber=?,password=?, credit=?, id_owner=? where id_card=?',
          [card.cardnumber, hash, card.credit,card.id_owner,id],
          callback);
        });
      },
      checkPassword: function(cardnumber,callback){
        return db.query('select password from card where cardnumber=?'
        ,[cardnumber],callback);
      }
  /*
  getById: function(id, callback) {
    return db.query('select id_card from card where cardnumber = ?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  add: function(add_card, callback) {
    bcrypt.hash(add_card.password, saltRounds, function(err, hash){
    return db.query(
      'insert into card (id_owner,cardnumber,password,credit) values (?,?,?,?)',
      [add_card.id_owner, add_card.cardnumber, hash,add_card.credit],
      callback);
    }); 
  },*/

 
    /*
  delete: function(id, callback) {
    return db.query('delete from card where id_card=?', [id], callback);
  },*/
 
}; 
module.exports = card;