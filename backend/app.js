var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var ownerRouter = require('./routes/owner');
var cardRouter = require('./routes/card');
var accountRouter = require('./routes/account');
var logsRouter = require('./routes/logs');

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/owner', ownerRouter);   // polku
app.use('/card', cardRouter);   //    ("/polku)
app.use('/account', accountRouter);
app.use('/logs', logsRouter);

module.exports = app;
