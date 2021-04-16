import React, { Component } from "react";

import { Typography, Box, Chip } from "@material-ui/core";
import { WEB_SOCKET_ROOT } from "../api";
import {
  WebSocketControllerProps,
  WebSocketFormLoader,
  WebSocketFormProps,
  webSocketController,
} from "../components";
import { SectionContent } from "../components";

import { ButtonState } from "./types";

export const BUTTON_URL = WEB_SOCKET_ROOT + "buttonState";

type Props = WebSocketControllerProps<ButtonState>;

class ButtonController extends Component<Props> {
  render() {
    return (
      <SectionContent title="Button Listener" titleGutter>
        <WebSocketFormLoader
          {...this.props}
          render={(props) => <ButtonControllerForm {...props} />}
        />
      </SectionContent>
    );
  }
}

export default webSocketController(BUTTON_URL, 100, ButtonController);

type FormProps = WebSocketFormProps<ButtonState>;

function ButtonControllerForm(props: FormProps) {
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
        <Typography variant="body1">Is the button pressed?</Typography>
      </Box>
      <Chip
        color={data.button_pressed ? "primary" : "default"}
        label={data.button_pressed ? "pressed" : "not pressed"}
      />
    </Box>
  );
}
