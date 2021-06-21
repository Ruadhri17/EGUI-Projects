import React, { Component } from 'react';

import { Button, Table, Container, Row, Col } from 'react-bootstrap';

class BasketMenu extends Component 
{  
    constructor(props)
    {
        super(props);
        this.state = 
        {
            'recipes': {},
            "userRecipes": [],
            "ingredients": [],
        }

    this.addUserChoice = this.addUserChoice.bind(this);
    this.deleteUserChoice = this.deleteUserChoice.bind(this);
    }
    
    componentDidMount() // fetch recipes from index 
    {
      fetch('/index')
      .then(response => response.json())
      .then((data) => {this.setState({'recipes': data})
        for (var recipe in data) // create array for ingredients
        {
            for (var ingredient in data[recipe]) 
            {
                if (ingredient !== "recipe") 
                {
                    var userIngredients = this.state.ingredients
                    userIngredients[ingredient] = []
                    this.setState({"ingredients": userIngredients}) 
                }
            }
        }
    });
    }
    
    addUserChoice(recipeToAdd) // add recipe to User choice list
    {
        var userRecipes = this.state.userRecipes; 
        userRecipes.push(recipeToAdd); // add new recipe
        this.setState({"userRecipes": userRecipes}); // update array content
        var recipeIngredients = this.state.recipes[recipeToAdd];
        for (var ingredient in recipeIngredients) 
        {
            if (ingredient !== "recipe") // omit recipe description
            {
                var check = this.state.ingredients[ingredient];
                var ingredientInfo = recipeIngredients[ingredient];
                if (check.length > 0) // if array of ingredients is not empty check if ingredient already is in array
                {
                    var updateIngredient = this.state.ingredients[ingredient];
                    var i = 0;
                    var unit = ingredientInfo.split(' '); //separate unit and quantity
                    var quantity = unit.shift();
                    check.forEach((element) => {
                        var checkUnit = element.split(' ');
                        var checkQuantity = checkUnit.shift();
                        if (unit[0] === checkUnit[0]) // check if units is the same
                        {
                            checkQuantity = parseFloat(quantity) + parseFloat(checkQuantity); // add quantity
                            var quantityAndUnit = checkQuantity.toFixed(2) + " " + unit[0]; // connect quantity and unit
                            updateIngredient.splice(i, i + 1); // remove previous state
                            updateIngredient.push(quantityAndUnit); // update
                        } 
                        else 
                        {
                            var quantityAndUnit = quantity + " " + unit[0]; // remove previous state
                            updateIngredient.push(quantityAndUnit); // update
                        }
                        i++;
                    })
                    var currentIngredient = this.state.ingredients ;
                    currentIngredient[ingredient] = updateIngredient;
                    this.setState({"ingredients": currentIngredient}); // preserve ingredients in array
                } 
                else // is array is empty simply add first element
                {
                    check.push(ingredientInfo);
                    var currentIngredient = this.state.ingredients;
                    currentIngredient[ingredient] = check;
                    this.setState({"ingredients": currentIngredient});
                }
            }
        }
    }
    
    deleteUserChoice(recipeToDelete)
    {
        var userRecipes = this.state.userRecipes // current user recipes
        for( var i = 0; i < userRecipes.length; i++)
        { 
            if ( userRecipes[i] === recipeToDelete) //find recipe that should be deleted 
            { 
                userRecipes.splice(i, 1);
                break; 
            }
        }
        this.setState({"addedRecipes": userRecipes}); // update recipe array
        var recipeIngredients = this.state.recipes[recipeToDelete];
        for (var ingredient in recipeIngredients) 
        {
            if (ingredient !== "recipe") // omit description
            {
                var check = this.state.ingredients[ingredient];
                var ingredientInfo = recipeIngredients[ingredient];
                if (check .length > 0) // if basket is not empty compare quantity and unit
                {
                    var updateIngredient = this.state.ingredients[ingredient];
                    var i = 0;
                    var unit = ingredientInfo.split(' ');
                    var quantity = unit.shift();
                    check.forEach((element) => {
                        var checkUnit = element.split(' ');
                        var checkQuantity = checkUnit.shift();
                        if (checkUnit[0] === unit[0]) // if unit is the same substract quantity
                        {
                            checkQuantity =  parseFloat(checkQuantity) - parseFloat(quantity);
                            if (checkQuantity > 0 ) 
                            {
                                var quantityAndUnit = checkQuantity.toFixed(2) + " " + unit[0]; // combine unit and quantity
                                updateIngredient.splice(i, i + 1);
                                updateIngredient.push(quantityAndUnit); // remove previous state and update
                            } 
                            else 
                                updateIngredient.splice(i, 1); // if quantity is equal 0, remove ingredient
                        }
                        i++;
                    })
                    var currentIngredient = this.state.ingredients; // update ingredient list
                    currentIngredient[ingredient] = updateIngredient;
                    this.setState({"ingredients": currentIngredient})
                }  
            }
        }
    }

    returnMenu()
    {
        window.location.href = "/" // back to previous window (Main menu)
    }
    render()
    {
        var availableRecipes = []; // display available recipes
        var readRecipes = this.state.recipes;
        for (var recipe in readRecipes)
        {
            var insertRow = (
                <>
                    <tr>
                        <th>{recipe}</th>
                        <th><Button variant="secondary" onClick={this.addUserChoice.bind(this, recipe)}>Add</Button></th>
                    </tr>
                </>
            )
        availableRecipes.push(insertRow);
        }
        var userRecipes = []; // display user choice recipes
        var chooseRecipes = this.state.userRecipes.values();
        for ( let recipe of chooseRecipes)
        {
            insertRow = (
                <>
                    <tr>
                        <th>{recipe}</th>
                        <th><Button variant="secondary" onClick={this.deleteUserChoice.bind(this, recipe)}>Delete</Button></th>
                    </tr>
                </>
            )
        userRecipes.push(insertRow);
        }
        var userIngredients = []; // display calculated ingredients
        var chooseIngredients = this.state.ingredients
        var ingredientName = Object.keys(chooseIngredients).sort()
        for (var i = 0; i < ingredientName.length; i++ ) 
        {
            if ( chooseIngredients[ingredientName[i]].length > 0) 
            {
                chooseIngredients[ingredientName[i]].forEach((quantityAndUnit) => {
                    insertRow = (
                        <>
                        <tr>
                            <th>{ingredientName[i]}</th>
                            <th>{quantityAndUnit}</th>
                        </tr>
                        </>
                    )
                    userIngredients.push(insertRow);
                })
                
            } 
        
        }
        return(
            <>
            <Container>
                <Row>
                    <Col>
                        <Table bordered variant="dark" className="mt-5">
                            <thead>
                                <tr>
                                    <th>Recipe</th>
                                    <th>Action</th>
                                </tr>
                            </thead>
                            <tbody>{availableRecipes}</tbody>
                        </Table>
                    </Col>
                    <Col>
                        <Table bordered variant="dark" className="mt-5">
                            <thead>
                                <tr>
                                    <th>Recipe</th>
                                    <th>Action</th>
                                </tr>
                            </thead>
                            <tbody>{userRecipes}</tbody>
                        </Table>
                    </Col>
                </Row>
                <Row>
                    <Table bordered variant="dark" className="mt-5">
                            <thead>
                                <tr>
                                    <th>Ingredient</th>
                                    <th>Unit and Quantity</th>
                                </tr>
                            </thead>
                            <tbody>{userIngredients}</tbody>
                    </Table>
                    <Button variant="secondary" onClick={this.returnMenu}>Return</Button>
                </Row>
            </Container>
            </>
        );
    }
}
export default BasketMenu
