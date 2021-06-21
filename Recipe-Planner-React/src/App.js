import './App.css';

import React, { Component } from 'react';
import { BrowserRouter as Router, Switch, Route} from 'react-router-dom';

import RecipeList from './RecipeList'
import BasketMenu from './BasketMenu'
import AddRecipe from './AddRecipe'
import EditRecipe from './EditRecipe'

import { NavBar } from './components/NavBar'
import { Layout } from './components/Layout'
import { Footer } from './components/Footer'

class App extends Component {

  render() {
    return (  
      <div>
      <React.Fragment>
        <NavBar />
        <Layout>    
          <Router>
            <Switch>
              <Route exact path="/" component={ RecipeList }/>
              <Route path="/AddRecipe" component={ AddRecipe }/> 
              <Route path="/EditRecipe" component={ EditRecipe }/> 
              <Route path="/BasketMenu" component={ BasketMenu }/> 
            </Switch>
          </Router>
        </Layout> 
        <Footer />
      </React.Fragment>
      </div>
    );
  }
}

export default App;
