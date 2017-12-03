let component = ReasonReact.statelessComponent("PlayerControls");

let str = ReasonReact.stringToElement;

let make = (~onClickPlay, ~onClickNext, ~isPlaying, _children) => {
  ...component,
  render: (_self) =>
    <div>
      <button onClick=onClickPlay>
        (str(isPlaying ? "Pause" : "Play"))
      </button>
      <button onClick=onClickNext> (str("Next")) </button>
    </div>
};
