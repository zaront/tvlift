import React, { Component } from 'react';
import { TextValidator, ValidatorForm } from 'react-material-ui-form-validator';

import { Typography, Box } from '@material-ui/core';
import SaveIcon from '@material-ui/icons/Save';

import { ENDPOINT_ROOT } from '../api';
import { restController, RestControllerProps, RestFormLoader, RestFormProps, FormActions, FormButton, SectionContent } from '../components';

import { LiftSettings } from './types';

export const LIFT_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "liftSettings";

type Props = RestControllerProps<LiftSettings>;

class LiftSettingsController extends Component<Props> {

  componentDidMount() {
    this.props.loadData();
  }

  render() {
    return (
      <SectionContent title='Settings' titleGutter>
        <RestFormLoader
          {...this.props}
          render={props => (
            <LiftSettingsForm {...props} />
          )}
        />
      </SectionContent>
    )
  }

}

export default restController(LIFT_SETTINGS_ENDPOINT, LiftSettingsController);

type FormProps = RestFormProps<LiftSettings>;

function LiftSettingsForm(props: FormProps) {
  const { data, saveData, handleValueChange } = props;
  return (
    <ValidatorForm onSubmit={saveData}>
      <Box bgcolor="primary.main" color="primary.contrastText" p={2} mt={2} mb={2}>
        <Typography variant="body1">
          Update the settings used by the TV Lift
        </Typography>
      </Box>
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
      <FormActions>
        <FormButton startIcon={<SaveIcon />} variant="contained" color="primary" type="submit">
          Save
        </FormButton>
      </FormActions>
    </ValidatorForm>
  );
}
