import React, { Component } from "react";

import { CssBaseline } from "@material-ui/core";
import {
  MuiThemeProvider,
  createMuiTheme,
  StylesProvider,
} from "@material-ui/core/styles";
import { amber, pink, deepPurple } from "@material-ui/core/colors";

const theme = createMuiTheme({
  palette: {
    primary: {
      main: "#adc32b",
    },
    secondary: {
      main: "#ac40db",
    },
    info: {
      main: deepPurple[700],
    },
    warning: {
      main: amber[600],
    },
    error: {
      main: pink[800],
    },
    success: {
      main: "#2f4800",
    },
  },
});

export default class CustomMuiTheme extends Component {
  render() {
    return (
      <StylesProvider>
        <MuiThemeProvider theme={theme}>
          <CssBaseline />
          {this.props.children}
        </MuiThemeProvider>
      </StylesProvider>
    );
  }
}
