import React, { Component } from "react";

import {
  Box,
  Chip,
  Typography,
  Divider,
} from "@material-ui/core";
import { WEB_SOCKET_ROOT } from "../api";
import {
  WebSocketControllerProps,
  WebSocketFormLoader,
  WebSocketFormProps,
  webSocketController,
  SectionContent,
} from "../components";
import RadioButtonUncheckedIcon from "@material-ui/icons/RadioButtonUnchecked";
import RadioButtonCheckedIcon from "@material-ui/icons/RadioButtonChecked";
import CastIcon from "@material-ui/icons/Cast";
import SettingsRemoteIcon from "@material-ui/icons/SettingsRemote";
import MyLocationIcon from "@material-ui/icons/MyLocation";
import MotorcycleIcon from "@material-ui/icons/Motorcycle";

import { LiftState } from "./types";

type Props = WebSocketControllerProps<LiftState>;

class StatusBar extends Component<Props> {
  render() {
    return (
      <SectionContent title="Lift Status" titleGutter>
        <WebSocketFormLoader
          {...this.props}
          render={(props) => <StatusBarForm {...props} />}
        />
      </SectionContent>
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
    <Box display="flex" flexWrap="wrap" flexDirection="column">
      <Box display="flex" p={1} alignItems="center">
        <Box mr={2}>
          <MotorcycleIcon fontSize="large" color="action" />
        </Box>
        <Box display="flex" flexDirection="column">
          <Typography variant="subtitle2">{data.motorState}</Typography>
          <Typography variant="caption" color="textSecondary">
            motor
          </Typography>
        </Box>
      </Box>

      <Divider />

      <Box display="flex" p={1} alignItems="center">
        <Box mr={2}>
          <MyLocationIcon fontSize="large" color="action" />
        </Box>
        <Box display="flex" flexDirection="column">
          <Typography variant="subtitle2">{data.position}</Typography>
          <Typography variant="caption" color="textSecondary">
            position
          </Typography>
        </Box>
      </Box>

      <Divider />

      <Box display="flex" p={1} alignItems="center">
        <Box mr={2}>
          <CastIcon fontSize="large" color="action" />
        </Box>
        <Box display="flex" flexDirection="column">
          <Typography variant="subtitle2">{data.chromecastStatus}</Typography>
          <Typography variant="caption" color="textSecondary">
            chromecast
          </Typography>
        </Box>
      </Box>

      <Divider />

      <Box p={1}>
        <Chip
          label="TV Code"
          color={data.sendingTvCode ? "primary" : "default"}
          icon={<SettingsRemoteIcon />}
        />
      </Box>

      <Box p={1}>
        <Chip
          label="Hidden Button"
          color={data.buttonPressed ? "primary" : "default"}
          icon={
            data.buttonPressed ? (
              <RadioButtonCheckedIcon />
            ) : (
              <RadioButtonUncheckedIcon />
            )
          }
        />
      </Box>

      <Box p={1}>
        <Chip
          label="Limit Switch"
          color={data.limitSwitchPressed ? "primary" : "default"}
          icon={
            data.limitSwitchPressed ? (
              <RadioButtonCheckedIcon />
            ) : (
              <RadioButtonUncheckedIcon />
            )
          }
        />
      </Box>

    </Box>
  );
}
