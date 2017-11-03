const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const paginate = require('express-paginate');
const mongoosePaginate = require('mongoose-paginate');
	
app.use(express.static(__dirname + '/client'));
app.use(bodyParser.json());

Genre = require('./models/genre');
Book = require('./models/book');

// Connect to Mongoose
mongoose.connect('mongodb://localhost/bookstore');
var db = mongoose.connection;

// app.all((req, res, next) => {
// 	if (req.body.limit <= 2) req.body.limit = 2;
// 	next();
// });

app.get('/', (req, res) => {
	res.send('Please use /api/books or /api/genres');
});

app.get('/api/genres', (req, res) => {
	Genre.getGenres((err, genres) => {
		if(err) throw err;
		res.json(genres);
	});
});

app.post('/api/genres', (req, res, next) => {
	var genre = req.body;
	Genre.addGenre(genre, (err, genre) => {
		if(err) throw err;
		res.json(genre);
	});
});

app.put('/api/genres/:_id', (req, res) => {
	var id = req.params._id;
	var genre = req.body;
	Genre.updateGenre(id, genre, {}, (err, genre) => {
		if(err) throw err;
		res.json(genre);
	});
});

app.delete('/api/genres/:_id', (req, res) => {
	// if (!db.find({"_id": req.params._id})) {
	// 	throw err;
	// }
	var id = req.params._id;
	Genre.removeGenre(id, (err, genre) => {
		if(err) throw err;
		res.json(genre);
	});
});

app.get('/api/books', (req, res, next) => {
	Book.getBooks((err, books) => {
		if(err) throw err;
		res.json(books);
	});
});

app.get('/api/books/:_id', (req, res) => {
	Book.getBookById(req.params._id, (err, book) => {
		if(err) throw err;
		res.json(book);
	});
});

app.post('/api/books', (req, res) => {
	var book = req.body;
	Book.addBook(book, (err, book) => {
		if(err) throw err;
		res.json(book);
	});
});

app.put('/api/books/:_id', (req, res) => {
	var id = req.params._id;
	var book = req.body;
	Book.updateBook(id, book, {}, (err, book) => {
		if(err) throw err;
		res.json(book);
	});
});

app.delete('/api/books/:_id', (req, res) => {
	// if (!db.find({"_id": req.params._id})) {
	// 	throw err;
	// }
	var id = req.params._id;
	Book.removeBook(id, (err, book) => {
		if(err) throw err;
		res.json(book);
	});
});

//catch 404
app.use((req, res, next) => {
	var err = new Error('Not Found');
	err.status = 404;
	next();
});

app.listen(3000);
console.log('Running on port 3000...');
