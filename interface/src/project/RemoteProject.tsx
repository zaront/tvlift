import React, { Component } from "react";
import { Redirect, Switch, RouteComponentProps } from "react-router-dom";

import { Tabs, Tab } from "@material-ui/core";

import { PROJECT_PATH } from "../api";
import { MenuAppBar } from "../components";
import { AuthenticatedRoute } from "../authentication";

import LightStateRestController from "./LightStateRestController";
import LightStateWebSocketController from "./LightStateWebSocketController";
import MotorController from "./MotorController";
import ButtonController from "./ButtonController";

class DemoProject extends Component<RouteComponentProps> {
  handleTabChange = (event: React.ChangeEvent<{}>, path: string) => {
    this.props.history.push(path);
  };

  render() {
    return (
      <MenuAppBar sectionTitle="TV Lift Remote">
        <Tabs
          value={this.props.match.url}
          onChange={this.handleTabChange}
          variant="fullWidth"
        >
          <Tab value={`/${PROJECT_PATH}/remote/rest`} label="REST Controller" />
          <Tab
            value={`/${PROJECT_PATH}/remote/socket`}
            label="WebSocket Controller"
          />
          <Tab value={`/${PROJECT_PATH}/remote/motor`} label="Motor Light" />
          <Tab value={`/${PROJECT_PATH}/remote/button`} label="Button" />
        </Tabs>
        <Switch>
          <AuthenticatedRoute
            exact
            path={`/${PROJECT_PATH}/remote/rest`}
            component={LightStateRestController}
          />
          <AuthenticatedRoute
            exact
            path={`/${PROJECT_PATH}/remote/socket`}
            component={LightStateWebSocketController}
          />
          <AuthenticatedRoute
            exact
            path={`/${PROJECT_PATH}/remote/motor`}
            component={MotorController}
          />
          <AuthenticatedRoute
            exact
            path={`/${PROJECT_PATH}/remote/button`}
            component={ButtonController}
          />
          <Redirect to={`/${PROJECT_PATH}/remote/socket`} />
        </Switch>
      </MenuAppBar>
    );
  }
}

export default DemoProject;
