import React, { useCallback, useEffect, useReducer } from "react";
import { SectionContent } from "../components";
import { ENDPOINT_ROOT } from "../api";
import {
  Box,
  Checkbox,
  Chip,
  createStyles,
  FormControlLabel,
  List,
  ListItem,
  ListItemIcon,
  ListItemText,
  makeStyles,
  Theme,
  useTheme,
} from "@material-ui/core";
import { useStorage } from "../components/useStorage";

interface LogItem {
  text: string;
  type: string;
  color: string;
  textColor: string;
}

const useStyles = makeStyles((theme: Theme) =>
  createStyles({
    item: {
      paddingLeft: theme.spacing(2),
    },
  })
);

const SystemLogController = (props: { showIfEnabled: boolean }) => {
  //hooks
  const theme = useTheme();
  const classes = useStyles(theme);
  const [log, appendLog] = useReducer(
    (state: Array<LogItem>, item: LogItem) => [item, ...state],
    []
  );
  const [showLog, setShowLog] = useStorage("showLog", false);

  const toLogItem = useCallback(
    (data: string) => {
      let text = data;
      let type = "";
      let color = "";
      let textColor = "";
      switch (data.substr(0, 3)) {
        case "V: ":
          text = data.substr(3);
          type = "verbose";
          break;
        case "T: ":
          text = data.substr(3);
          type = "trace";
          color = theme.palette.success.main;
          textColor = theme.palette.success.contrastText;
          break;
        case "N: ":
          text = data.substr(3);
          type = "notice";
          color = theme.palette.secondary.main;
          textColor = theme.palette.secondary.contrastText;
          break;
        case "W: ":
          text = data.substr(3);
          type = "warning";
          color = theme.palette.warning.main;
          textColor = theme.palette.warning.contrastText;
          break;
        case "E: ":
          text = data.substr(3);
          type = "error";
          color = theme.palette.error.main;
          textColor = theme.palette.error.contrastText;
          break;
        case "F: ":
          text = data.substr(3);
          type = "fatal";
          color = theme.palette.error.dark;
          textColor = theme.palette.error.contrastText;
          break;
      }
      return { text, type, color, textColor } as LogItem;
    },
    [theme.palette]
  );

  useEffect(() => {
    const eventSource = new EventSource(ENDPOINT_ROOT + "log");
    eventSource.onmessage = (e) => appendLog(toLogItem(e.data as string));
    return () => {
      eventSource.close();
    };
  }, [toLogItem]);

  const onChange = (e: any, checked: boolean) => {
    setShowLog(checked);
  };

  //conditional rendering
  if (props.showIfEnabled && !showLog)
    return null;

  return (
    <SectionContent
      title={
        <Box display="flex" flexDirection="row" justifyContent="space-between">
          <Box>System Log</Box>
          <FormControlLabel
            control={<Checkbox checked={showLog} onChange={onChange} />}
            label="show everywhere"
          />
        </Box>
      }
    >
      <List dense={true}>
        {log.map((i, index) => (
          <ListItem key={index}>
            <ListItemIcon>
              {i.type && (
                <Chip
                  label={i.type}
                  size="small"
                  style={{ background: i.color, color: i.textColor }}
                />
              )}
            </ListItemIcon>
            <ListItemText
              primary={i.text}
              style={{ color: i.color }}
              className={classes.item}
            />
          </ListItem>
        ))}
      </List>
    </SectionContent>
  );
};

export default SystemLogController;
