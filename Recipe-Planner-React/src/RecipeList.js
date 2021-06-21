import React, { Component } from 'react';

import postData from './comms';

import { ButtonGroup, Button, Table } from 'react-bootstrap';


class RecipeList extends Component 
{
  constructor(props) 
  {
    super(props);
    this.state = 
    {
      'recipes': {},
    }
  }

  componentDidMount()
  {
    fetch('/index') // fetch json file from backend 
      .then(response => response.json())
      .then(data => this.setState({'recipes': data}));
  }
  
  addRecipe()
  {
    window.location.href = "/AddRecipe"  // on add recipe button go to add recipe page
  }
  editRecipe(recipe)
  {
    window.location.href = "/EditRecipe/" + recipe // on edit recipe button go to edit recipe page and pass name of recipe as key
  }
  deleteRecipe(recipe)
  {
    var data = {"delete": recipe} 
    postData('http://localhost:5000/DeleteRecipe/' + recipe, data, 'DELETE') // send information to backend which recipe delete from json file
    var refreshRecipes = {};
    var currentRecipes = this.state.recipes
    for (var recipeName in currentRecipes) // remove recipe from view table and preserve rest of recipes
    {
      if ( recipeName === recipe ) 
        continue;
      else 
        refreshRecipes[recipeName] = currentRecipes[recipeName];
    }
    this.setState({'recipes': refreshRecipes})
  }
  openBasketMenu()
  {
    window.location.href = "/BasketMenu" // on basket menu button go to basket menu page
  }
  render() 
  {
    var index = 1;
    var recipes = [];
    var allRecipes = this.state.recipes
    for (var name in allRecipes) { // put recipes into table
      var insertRow = (
        <>
            <tr>
            <th>{index}</th>
            <th>{name}</th>
            <th><ButtonGroup>
            <Button variant="secondary" onClick={this.deleteRecipe.bind(this, name)}>Delete</Button>
            <Button variant="secondary" onClick={this.editRecipe.bind(this, name)}>Edit</Button>
            </ButtonGroup></th>
            </tr>
        </>
      )
      recipes.push(insertRow);
      index++;
    }
    return (
      <>
        <Table bordered variant="dark" className="mt-5">
            <thead>
                <tr>
                    <th>#</th>
                    <th>Recipe</th>
                    <th>Action</th>
                </tr>
            </thead>
            <tbody>{recipes}</tbody>
            
        </Table>
        <ButtonGroup>
            <Button variant="secondary"className="mr-3" onClick={this.addRecipe}>Add Recipe</Button>
            <Button variant="secondary" onClick={this.openBasketMenu}>Basket Menu</Button>
        </ButtonGroup>
        </>
    );
  }
}
export default RecipeList;