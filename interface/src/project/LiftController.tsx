import React, { Component } from "react";
import { Typography, Box, Button, ButtonGroup } from "@material-ui/core";
import { WEB_SOCKET_ROOT } from "../api";
import {
  WebSocketControllerProps,
  WebSocketFormLoader,
  WebSocketFormProps,
  webSocketController,
} from "../components";
import { SectionContent } from "../components";
import { LiftCommand } from "./types";
import ArrowDropUpIcon from "@material-ui/icons/ArrowDropUp";
import ArrowDropDownIcon from "@material-ui/icons/ArrowDropDown";
import PowerIcon from "@material-ui/icons/Power";
import PowerOffIcon from "@material-ui/icons/PowerOff";
import PlayCircleFilledIcon from "@material-ui/icons/PlayCircleFilled";
import KeyboardArrowUpIcon from "@material-ui/icons/KeyboardArrowUp";
import KeyboardArrowDownIcon from "@material-ui/icons/KeyboardArrowDown";
import StopIcon from "@material-ui/icons/Stop";
import LockOpenIcon from "@material-ui/icons/LockOpen";
import LiftStatus from "./LiftStatus";

type Props = WebSocketControllerProps<LiftCommand>;

class LiftController extends Component<Props> {
  render() {
    return (
      <>
        <SectionContent title="Remote Control" titleGutter>
          <WebSocketFormLoader
            {...this.props}
            render={(props) => <LiftForm {...props} />}
          />
        </SectionContent>
        <LiftStatus />
      </>
    );
  }
}

export default webSocketController(
  WEB_SOCKET_ROOT + "liftCommand",
  100,
  LiftController
);

type FormProps = WebSocketFormProps<LiftCommand>;

function LiftForm(props: FormProps) {
  const { data, setData, saveData } = props;

  const sendCommand = (command: LiftCommand) => {
    setData(command, saveData);
  };

  return (
    <Box>
      <Box display="flex" flexWrap="wrap">
        <Box p={1}>
          <ButtonGroup orientation="vertical">
            <Button
              onClick={() => sendCommand({ command: "up", amount: 0 })}
              variant={data.command === "up" ? "contained" : "outlined"}
              disableElevation
              startIcon={<ArrowDropUpIcon />}
            >
              Up
            </Button>
            <Button
              onClick={() => sendCommand({ command: "down", amount: 0 })}
              variant={data.command === "down" ? "contained" : "outlined"}
              disableElevation
              startIcon={<ArrowDropDownIcon />}
            >
              Down
            </Button>
          </ButtonGroup>
        </Box>

        <Box p={1}>
          <ButtonGroup orientation="vertical">
            <Button
              onClick={() => sendCommand({ command: "nudge_up", amount: 2000 })}
              variant={data.command === "nudge_up" ? "contained" : "outlined"}
              disableElevation
              startIcon={<KeyboardArrowUpIcon />}
            >
              Nudge Up
            </Button>
            <Button
              onClick={() =>
                sendCommand({ command: "nudge_down", amount: 2000 })
              }
              variant={data.command === "nudge_down" ? "contained" : "outlined"}
              disableElevation
              startIcon={<KeyboardArrowDownIcon />}
            >
              Nudge Down
            </Button>
          </ButtonGroup>
        </Box>

        <Box p={1}>
          <Button
            onClick={() => sendCommand({ command: "stop", amount: 2000 })}
            variant={data.command === "stop" ? "contained" : "outlined"}
            disableElevation
            startIcon={<StopIcon />}
          >
            Stop
          </Button>
        </Box>

        <Box p={1}>
          <Button
            onClick={() => sendCommand({ command: "motor_off", amount: 2000 })}
            variant={data.command === "motor_off" ? "contained" : "outlined"}
            disableElevation
            startIcon={<LockOpenIcon />}
          >
            Motor Off
          </Button>
        </Box>

        <Box p={1}>
          <ButtonGroup orientation="vertical">
            <Button
              onClick={() => sendCommand({ command: "tv_on", amount: 2000 })}
              variant={data.command === "tv_on" ? "contained" : "outlined"}
              disableElevation
              startIcon={<PowerIcon />}
            >
              TV On
            </Button>
            <Button
              onClick={() => sendCommand({ command: "tv_off", amount: 2000 })}
              variant={data.command === "tv_off" ? "contained" : "outlined"}
              disableElevation
              startIcon={<PowerOffIcon />}
            >
              TV Off
            </Button>
          </ButtonGroup>
        </Box>

        <Box p={1}>
          <Button
            onClick={() => sendCommand({ command: "automatic", amount: 2000 })}
            variant={data.command === "automatic" ? "contained" : "outlined"}
            disableElevation
            startIcon={<PlayCircleFilledIcon />}
          >
            Automatic
          </Button>
        </Box>
      </Box>
    </Box>
  );
}
