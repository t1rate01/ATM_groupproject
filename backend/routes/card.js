const express = require('express');
const router = express.Router();
const card = require('../models/card_model');


router.post('/debitwithdraw', 
function(request, response) {
  card.debitwithdraw(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      response.json(dbResult);
    }
  });
});

router.post('/creditwithdraw', 
function(request, response) {
  card.creditwithdraw(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      response.json(dbResult);
    }
  });
});

router.post('/cid', 
function(request, response) {
  card.getcardid(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult[0]);
    }
  });
});

router.post('/cred', 
function(request, response) {
  card.getcardcred(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult[0]);
    }
  });
});

router.put('/:id', 
function(request, response) {
  card.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});
/* router.get('/',
    function (request, response) {
        card.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });
*/
/*
router.get('/idcard/:id?',
    function (request, response) {
        card.getById(request.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult[0]);
            }
        })
    });
*/

/*
router.post('/', 
function(request, response) {
  card.add(request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(request.body);
      response.json(dbResult.rows);
    }
  });
});*/



/*
router.delete('/:id', 
function(request, response) {
  card.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});
*/



module.exports = router;
