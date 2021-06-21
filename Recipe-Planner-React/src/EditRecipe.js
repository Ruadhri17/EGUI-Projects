import React, { Component } from 'react';
import postData from './comms';
import {withRouter} from 'react-router-dom';

import { ButtonGroup, Button, Table, Container, Form, Row, Col } from 'react-bootstrap';

class EditRecipe extends Component 
{
    constructor(props) 
    {
        super(props);
        this.state = 
        {
            "recipes": {}
        }
        this.onChange = this.onChange.bind(this);
        this.changeName = this.changeName.bind(this);
        this.changeDescription = this.changeDescription.bind(this);
        this.addIngredient = this.addIngredient.bind(this);
        this.deleteIngredient = this.deleteIngredient.bind(this);
        this.submitRecipe = this.submitRecipe.bind(this);
        this.cancelRecipe =  this.cancelRecipe.bind(this);
    }
    componentDidMount()
    {
        fetch("http://localhost:5000" + window.location.pathname)
          .then(response => response.json())
          .then(data => this.setState({'recipes': JSON.parse(data)}));
    }
    onChange = (change) => 
    {
        this.setState({ [change.target.name]: change.target.value });
    }
    
    changeName(change) // update name 
    {
        var recipeName = Object.keys(this.state.recipes);
        var data = this.state.recipes.[recipeName[0]];
        this.setState({'recipes': {[change.target.value]: data}});
    }
    
    changeDescription(change) //  update description
    {
        var recipeName = Object.keys(this.state.recipes);
        var data = change.target.value.split("\n");
        var state = this.state.recipes;
        state[recipeName[0]]['recipe'] = data;
        this.setState({'recipes': state});
    }
    addIngredient() // add ingredient
    {
        var recipeName = Object.keys(this.state.recipes);
        var quantity_and_unit = this.state.IngredientQuantity.toString() + " " + this.state.IngredientUnit;
        var data = this.state.recipes.[recipeName[0]];
        data[this.state.IngredientName] = quantity_and_unit;
        this.setState({'recipes': {[recipeName[0]]: data}});
    }
    
    deleteIngredient(nameToDelete) // delete ingredient 
    {
        var recipeName = Object.keys(this.state.recipes);
        var allIngredients = this.state.recipes.[recipeName[0]];
        var preserveIngredients = {};
        for (var names in allIngredients) 
        {
            if (names === nameToDelete) // find ingredient with that name and delete it
                continue;
            else 
                preserveIngredients[names] = allIngredients[names]; // preserve rest of ingredients
        }
        this.setState({'recipes': {[recipeName[0]]: preserveIngredients}})
    }
  
    submitRecipe()
    {
        var data = this.state.recipes
        postData('http://localhost:5000' + window.location.pathname, data, "POST"); // send data to backend using POST
        this.props.history.push('/'); // after sending data, come back to main menu
    }
    cancelRecipe()
    {
        window.location.href = "/"; // back to main menu
    }

    render() {
    var index = 1; 
    var recipeName = Object.keys(this.state.recipes);
    var allIngredients = this.state.recipes.[recipeName[0]];
    var displayIngredients = [];
    for (var DescOrIngr in allIngredients) // split ingredient for name, quantity and unit to display in table
    {
        if ( DescOrIngr  === 'recipe' ) 
        {
            var descripion_lines = allIngredients[DescOrIngr]
            descripion_lines = descripion_lines.join("\n");
        } 
        else 
        {
            var ingredientName = DescOrIngr;
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
                        <Form.Control type="text" name="RecipeName" id="RecipeName" defaultValue={recipeName[0]} onChange={this.changeName} placeholder="Please enter recipe name" required />
                    </Form.Group>
                    <Form.Group className="mb-3" controlId="RecipeDescription">
                        <Form.Label>Recipe Description</Form.Label>
                        <Form.Control as="textarea" name="RecipeDescription" id="RecipeDescription" defaultValue={descripion_lines} onChange={this.changeDescription} rows={5} placeholder="Please enter recipe description" required />
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
  
  export default withRouter(EditRecipe);