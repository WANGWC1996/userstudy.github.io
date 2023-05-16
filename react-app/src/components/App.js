import React from "react";
import Welcome from "./Welcome";
import Interaction from "./Interaction";
import Result from "./Result";
import End from "./End"
import { connect } from "react-redux";

function App({ activeComponent }) {
  switch (activeComponent) {
    case "Welcome":
      return <Welcome />;
    case "Interaction":
      return <Interaction />;
    case "Result":
      return <Result />;
    case "End":
      return <End />;
    default:
      return <div />;
  }
}

const mapStateToProps = ({ activeComponent }) => ({
  activeComponent
});

export default connect(mapStateToProps)(App);
