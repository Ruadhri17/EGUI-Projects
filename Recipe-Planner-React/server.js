const express = require('express');
const app = express();
const port = 5000;
const path = require('path');
const fs = require('fs');
const bodyParser = require('body-parser');
var cors = require('cors')
	app.use(bodyParser.json());
  	app.use(cors());

// read json
app.get('/index', (req, res) => {
	var readJson = fs.readFileSync('recipes.json');
	res.json(JSON.parse(readJson));
});

// add recipe 
app.post('/AddRecipe', (req, res) => {
	var writeJson = {};
	var readJson = JSON.parse(fs.readFileSync('recipes.json'));
	for (var recipes in readJson) 
		writeJson[recipes] = readJson[recipes];
	var addRecipe = req.body;
	for (var recipes in addRecipe)
		writeJson[recipes] = addRecipe[recipes];
	fs.writeFileSync('recipes.json', JSON.stringify(writeJson), 'utf-8');
})
// delete recipe
app.delete('/DeleteRecipe/:key', (req, res) => {
	const recipeToDelete = req.params.key;
	var readJson = JSON.parse(fs.readFileSync('recipes.json'));
	var recipes = {};
	for (var recipe in readJson) 
	{
		if ( recipe == recipeToDelete) 
			continue;
		else 
			recipes[recipe] = readJson[recipe];
	}
	fs.writeFileSync('recipes.json', JSON.stringify(recipes), 'utf-8');
})
// get info of edited recipe
app.get('/EditRecipe/:key', (req, res) => {
		const recipeToEdit = req.params.key;
		var readJson = JSON.parse(fs.readFileSync('recipes.json'));
		var response = {[recipeToEdit]: readJson[recipeToEdit]}
		res.json(JSON.stringify(response));
})
// edit recipe 
app.post('/EditRecipe/:key', (req, res) => {
	var recipeToEdit = req.params.key
	var writeJson = {};
	var readJson = JSON.parse(fs.readFileSync('recipes.json'));
	for (var recipe in readJson) 
	{
		if ( recipe === recipeToEdit) 
			continue;
		else 
			writeJson[recipe] = readJson[recipe];
	}
	var editRecipe =  req.body;
	for ( var edited in editRecipe ) 
		writeJson[edited] = editRecipe[edited];
	fs.writeFileSync('recipes.json', JSON.stringify(writeJson), 'utf-8');
})

app.listen(port, () => console.log(`listening port 5000`));

