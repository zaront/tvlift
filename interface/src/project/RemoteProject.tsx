import React, { Component } from "react";
import { Redirect, Switch, RouteComponentProps } from "react-router-dom";

import { Tabs, Tab } from "@material-ui/core";

import { PROJECT_PATH } from "../api";
import { MenuAppBar } from "../components";
import { AuthenticatedRoute } from "../authentication";

import LiftController from "./LiftController";
import LiftSettingsController from "./LiftSettingsController";

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
          <Tab value={`/${PROJECT_PATH}/remote`} label="Remote Control" />
          <Tab value={`/${PROJECT_PATH}/remote/settings`} label="Settings" />
        </Tabs>
        <Switch>
          <AuthenticatedRoute
            exact
            path={`/${PROJECT_PATH}/remote`}
            component={LiftController}
          />
          <AuthenticatedRoute
            exact
            path={`/${PROJECT_PATH}/remote/settings`}
            component={LiftSettingsController}
          />
          <Redirect to={`/${PROJECT_PATH}/remote`} />
        </Switch>
      </MenuAppBar>
    );
  }
}

export default DemoProject;
