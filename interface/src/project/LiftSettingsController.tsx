import React, { Component } from 'react';
import { TextValidator, ValidatorForm } from 'react-material-ui-form-validator';

import SaveIcon from '@material-ui/icons/Save';

import { ENDPOINT_ROOT } from '../api';
import { restController, RestControllerProps, RestFormLoader, RestFormProps, FormActions, FormButton, SectionContent } from '../components';

import { LiftSettings } from './types';
import LiftStatus from './LiftStatus';

export const LIFT_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "liftSettings";

type Props = RestControllerProps<LiftSettings>;

class LiftSettingsController extends Component<Props> {

  componentDidMount() {
    this.props.loadData();
  }

  render() {
    return (
      <>
      <SectionContent title='Settings' titleGutter>
        <RestFormLoader
          {...this.props}
          render={props => (
            <LiftSettingsForm {...props} />
          )}
        />
      </SectionContent>
      <LiftStatus/>
      </>
    )
  }

}

export default restController(LIFT_SETTINGS_ENDPOINT, LiftSettingsController);

type FormProps = RestFormProps<LiftSettings>;

function LiftSettingsForm(props: FormProps) {
  const { data, saveData, handleValueChange } = props;
  return (
    <ValidatorForm onSubmit={saveData}>
      <TextValidator
          validators={['required', 'isNumber', 'minNumber:0', 'maxNumber:20']}
          errorMessages={['Port is required', "Must be a number", "Must be greater than 0 ", "Max value is 20"]}
          name="maxPosition"
          label="Highest Position"
          fullWidth
          variant="outlined"
          value={data.maxPosition}
          type="number"
          onChange={handleValueChange('maxPosition')}
          margin="normal"
        />
        <TextValidator
          validators={['required', 'isNumber', 'minNumber:0', 'maxNumber:20']}
          errorMessages={['Port is required', "Must be a number", "Must be greater than 0 ", "Max value is 20"]}
          name="minPosition"
          label="Lowest Position"
          fullWidth
          variant="outlined"
          value={data.minPosition}
          type="number"
          onChange={handleValueChange('minPosition')}
          margin="normal"
        />
        <TextValidator
          validators={['required', 'isNumber', 'minNumber:0', 'maxNumber:20']}
          errorMessages={['Port is required', "Must be a number", "Must be greater than 0 ", "Max value is 20"]}
          name="maxSpeed"
          label="Top Speed"
          fullWidth
          variant="outlined"
          value={data.maxSpeed}
          type="number"
          onChange={handleValueChange('maxSpeed')}
          margin="normal"
        />
        <TextValidator
          validators={['required', 'isNumber', 'minNumber:0', 'maxNumber:20']}
          errorMessages={['Port is required', "Must be a number", "Must be greater than 0 ", "Max value is 20"]}
          name="acceleration"
          label="Acceleration"
          fullWidth
          variant="outlined"
          value={data.acceleration}
          type="number"
          onChange={handleValueChange('acceleration')}
          margin="normal"
        />
        <TextValidator
          validators={['required', 'isNumber', 'minNumber:0', 'maxNumber:20']}
          errorMessages={['Port is required', "Must be a number", "Must be greater than 0 ", "Max value is 20"]}
          name="disconnectTimeout"
          label="Chromecast disconnection timeout"
          fullWidth
          variant="outlined"
          value={data.disconnectTimeout}
          type="number"
          onChange={handleValueChange('disconnectTimeout')}
          margin="normal"
        />
        <TextValidator
          name="tvCodeOn"
          label="TV on code"
          fullWidth
          variant="outlined"
          value={data.tvCodeOn}
          onChange={handleValueChange('tvCodeOn')}
          margin="normal"
        />
        <TextValidator
          name="tvCodeOff"
          label="TV off code"
          fullWidth
          variant="outlined"
          value={data.tvCodeOff}
          onChange={handleValueChange('tvCodeOff')}
          margin="normal"
        />
        <TextValidator
          name="chromecast"
          label="Chromecast device name"
          fullWidth
          variant="outlined"
          value={data.chromecast}
          onChange={handleValueChange('chromecast')}
          margin="normal"
        />
      <FormActions>
        <FormButton startIcon={<SaveIcon />} variant="contained" color="primary" type="submit">
          Save
        </FormButton>
      </FormActions>
    </ValidatorForm>
  );
}
