import React, { Component } from "react";

import { Typography, Box, Button } from "@material-ui/core";
import { WEB_SOCKET_ROOT } from "../api";
import {
  WebSocketControllerProps,
  WebSocketFormLoader,
  WebSocketFormProps,
  webSocketController,
} from "../components";
import { SectionContent } from "../components";

import { LiftCommand } from "./types";

type Props = WebSocketControllerProps<LiftCommand>;

class LiftController extends Component<Props> {

  render() {
    return (
      <SectionContent title="Remote Control" titleGutter>
        <WebSocketFormLoader
          {...this.props}
          render={(props) => <LiftForm {...props} />}
        />
      </SectionContent>
    );
  }
}

export default webSocketController(WEB_SOCKET_ROOT + "liftCommand", 100, LiftController);

type FormProps = WebSocketFormProps<LiftCommand>;

function LiftForm(props: FormProps) {
  const { data, setData, saveData } = props;

  const sendCommand = (command: LiftCommand) => {
    setData(command, saveData);
  }

  return (
    <Box>
      <Box
        bgcolor="primary.main"
        color="primary.contrastText"
        p={2}
        mt={2}
        mb={2}
      >
        <Typography variant="body1">Control the TV Lift</Typography>
      </Box>
      <Button onClick={() => sendCommand({command:"nudge_up", amount:0})}>
        Nudge Up
        </Button>
        <Button onClick={() => sendCommand({command:"nudge_down", amount:0})}>
        Nudge Down
        </Button>
    </Box>
  );
}
