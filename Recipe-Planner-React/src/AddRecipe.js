import React, { Component } from 'react';
import postData from './comms';
import {withRouter} from 'react-router-dom';

import { ButtonGroup, Button, Table, Container, Form, Row, Col } from 'react-bootstrap';

class AddRecipe extends Component 
{
    constructor(props) 
    {
        super(props);
        this.state = 
        {
            'ingredients': {},
            'RecipeName': '',
            'RecipeDescription': '',
            'IngredientName': '',
            'IngredientQuantity': '',
            'IngredientUnit': ''
        }
        this.onChange = this.onChange.bind(this);
        this.addIngredient = this.addIngredient.bind(this);
        this.deleteIngredient = this.deleteIngredient.bind(this);
        this.submitRecipe = this.submitRecipe.bind(this);
        this.cancelRecipe =  this.cancelRecipe.bind(this);
    }
  
    onChange = (change) => 
    {
      this.setState({ [change.target.name]: change.target.value }); // update state values
    }
  
    addIngredient()
    {
      if(this.state.IngredientName.length === 0 || this.state.IngredientUnit.length === 0) // if ingredient name or unit is empty, dont add it
        return;
      var quantity_and_unit = this.state.IngredientQuantity.toString() + " " + this.state.IngredientUnit; // merge quantity and unit
      var data = this.state.ingredients
      data[this.state.IngredientName] = quantity_and_unit;
      this.setState({'ingredients': data}) // update ingredient state
    }
  
    deleteIngredient(nameToDelete)
    {
      var allIngredients = this.state.ingredients;
      var preserveIngredients = {};
      for (var names in allIngredients) 
      {
        if (names === nameToDelete) 
            continue;
        else 
            preserveIngredients[names] = allIngredients[names] // preserve all other ingredients
      }
      this.setState({'ingredients': preserveIngredients}) // update state
    }
  
    submitRecipe()
    {
        if (this.state.RecipeName.length === 0) // if recipe name is empty do not add it
            return;
        var saveRecipe = {}
        saveRecipe[this.state.RecipeName] = {}
        saveRecipe[this.state.RecipeName]["recipe"] = this.state.RecipeDescription.split("\n"); // split description on lines
        var saveIngredients = this.state.ingredients
        for ( var ingredient in saveIngredients )
            saveRecipe[this.state.RecipeName][ingredient] = saveIngredients[ingredient];
        postData('http://localhost:5000/AddRecipe', saveRecipe, "POST") // send data to backend with POST
        this.props.history.push('/'); // back to main menu
    }
    
    cancelRecipe()
    {
        window.location.href = "/" // back to Main emu
    }

    render() {
    var index = 1;  // index for keeping order in table
    var allIngredients = this.state.ingredients
    var displayIngredients = [];
    for (var DescOrIngr in allIngredients) // saparate name quantity and unit for rows in table
    {
        if ( DescOrIngr  === 'recipe' ) 
        {
            var descripion_lines = allIngredients[DescOrIngr]
            descripion_lines = descripion_lines.join("\n");
        } 
        else 
        {
            var ingredientName = DescOrIngr
            var quantity_and_unit = allIngredients[DescOrIngr];
            var to_split = quantity_and_unit.indexOf(' ');
            var quantity  = quantity_and_unit.slice(0,to_split).trim();
            var unit  = quantity_and_unit.slice(to_split + 1, quantity_and_unit.length).trim();
            var insertRow = (
                <>
                    <tr>
                        <th>{index}</th>
                        <th>{ingredientName}</th>
                        <th>{quantity}</th>
                        <th>{unit}</th>
                        <th><Button variant="secondary" onClick={this.deleteIngredient.bind(this, ingredientName)}>Delete</Button></th>
                    </tr>
                </>
            )
            displayIngredients.push(insertRow);
            index++;
        }
    }
    return (
           <>
            <Container> 
                <Form hasValidation>
                    <Form.Group className="mb-3" controlId="RecipeName">
                        <Form.Label>Recipe Name</Form.Label>
                        <Form.Control type="text" name="RecipeName" id="RecipeName" placeholder="Please enter recipe name" onChange={this.onChange} required />
                    </Form.Group>
                    <Form.Group className="mb-3" controlId="RecipeDescription">
                        <Form.Label>Recipe Description</Form.Label>
                        <Form.Control as="textarea" name="RecipeDescription" id="RecipeDescription" rows={5} placeholder="Please enter recipe description" onChange={this.onChange} required />
                    </Form.Group>
                    <Row>
                        <Col>
                            <Table bordered variant="dark" className="mt-2">
                                <thead>
                                    <tr>
                                        <th>#</th>
                                        <th>Ingredient</th>
                                        <th>Quantity</th>
                                        <th>Unit</th>
                                        <th>Action</th>
                                    </tr>
                                </thead>
                                <tbody>{displayIngredients}</tbody>
                            </Table>
                        </Col>
                        <Col>
                            <Form.Group className="mb-3" controlId="IngredientName">
                                <Form.Label>Ingredient Name</Form.Label>
                                <Form.Control type="text" name="IngredientName" id="IngredientName" placeholder="Ingredient Name" onChange={this.onChange}/>
                            </Form.Group>
                            <Form.Group className="mb-3" controlId="IngredientQuantity">
                                <Form.Label>Ingredient Quantity</Form.Label>
                                <Form.Control type="number" name="IngredientQuantity" id="IngredientQuantity" placeholder="0.0" onChange={this.onChange}/>
                            </Form.Group>
                            <Form.Group className="mb-3" controlId="IngredientUnit">
                                <Form.Label>Ingredient Unit</Form.Label>
                                <Form.Control type="text" name="IngredientUnit" id="IngredientUnit" placeholder="Ingredient Unit" onChange={this.onChange}/>
                            </Form.Group>
                            <ButtonGroup className="float-right">
                                <Button variant="secondary" onClick={this.addIngredient}>Add Ingredient</Button>
                            </ButtonGroup>
                        </Col>
                    </Row> 
                    <ButtonGroup className="mt-5">
                    <Button type="submit" variant="secondary" className="mr-3" onClick={this.submitRecipe}>Save</Button>
                    <Button variant="secondary" onClick={this.cancelRecipe}>Cancel</Button>
                    </ButtonGroup>  
                </Form>   
            </Container>
          </>
      );
    }
  }
  
  export default AddRecipe;