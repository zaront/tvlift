import React, { Component } from 'react';
import { ValidatorForm } from 'react-material-ui-form-validator';

import { Typography, Box, Switch } from '@material-ui/core';
import { WEB_SOCKET_ROOT } from '../api';
import { WebSocketControllerProps, WebSocketFormLoader, WebSocketFormProps, webSocketController } from '../components';
import { SectionContent, BlockFormControlLabel } from '../components';

import { MotorState } from './types';

export const MOTOR_URL = WEB_SOCKET_ROOT + "motorState";

type Props = WebSocketControllerProps<MotorState>;

class MotorController extends Component<Props> {

  render() {
    return (
      <SectionContent title='Motor Controller' titleGutter>
        <WebSocketFormLoader
          {...this.props}
          render={props => (
            <MotorControllerForm {...props} />
          )}
        />
      </SectionContent>
    )
  }

}

export default webSocketController(MOTOR_URL, 100, MotorController);

type FormProps = WebSocketFormProps<MotorState>;

function MotorControllerForm(props: FormProps) {
  const { data, saveData, setData } = props;

  const changeLedOn = (event: React.ChangeEvent<HTMLInputElement>) => {
    setData({ led_on: event.target.checked }, saveData);
  }

  return (
    <ValidatorForm onSubmit={saveData}>
      <Box bgcolor="primary.main" color="primary.contrastText" p={2} mt={2} mb={2}>
        <Typography variant="body1">
          Turn the Motor light on or off
        </Typography>
      </Box>
      <BlockFormControlLabel
        control={
          <Switch
            checked={data.led_on}
            onChange={changeLedOn}
            color="primary"
          />
        }
        label="LED State?"
      />
    </ValidatorForm>
  );
}
