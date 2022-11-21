const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.cardnumber && request.body.password){
      const cardnumber = request.body.cardnumber;
      const password = request.body.password;
        card.checkPassword(cardnumber, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError.errno);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(password,dbResult[0].password, function(err,compareResult) {
                if(compareResult) {
                  console.log("success");
                  const token = generateAccessToken({ username: cardnumber });
                  response.send(token);
                }
                else {
                    console.log("wrong password");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("card does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{

      console.log("cardnumber or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
    dotenv.config();
    return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
  }
  

module.exports=router;
