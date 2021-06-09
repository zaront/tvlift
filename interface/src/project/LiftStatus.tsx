import React, { Component } from "react";

import { Typography, Box, Grid, Paper, Chip } from "@material-ui/core";
import { WEB_SOCKET_ROOT } from "../api";
import {
  WebSocketControllerProps,
  WebSocketFormLoader,
  WebSocketFormProps,
  webSocketController,
} from "../components";

import { LiftState } from "./types";

type Props = WebSocketControllerProps<LiftState>;

class StatusBar extends Component<Props> {
  render() {
    return (
      <WebSocketFormLoader
        {...this.props}
        render={(props) => <StatusBarForm {...props} />}
      />
    );
  }
}

export default webSocketController(
  WEB_SOCKET_ROOT + "liftStatus",
  100,
  StatusBar
);

type FormProps = WebSocketFormProps<LiftState>;

function StatusBarForm(props: FormProps) {
  const { data } = props;

  return (
    <Box>
      <Box
        bgcolor="primary.main"
        color="primary.contrastText"
        p={2}
        mt={2}
        mb={2}
      >
        <Typography variant="body1">Lift Status</Typography>
      </Box>
      <Grid container spacing={3}>
        <Grid item xs={12}>
          <Paper>xs=12: {data.liftStatus}</Paper>
        </Grid>
      </Grid>
      <Chip
        color={data.buttonPressed ? "primary" : "default"}
        label={data.buttonPressed ? "pressed" : "not pressed"}
      />
    </Box>
  );
}
