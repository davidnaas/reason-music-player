[%bs.raw {|require('./app.css')|}];

type state = {
  index: int,
  queue: array(string),
  isPlaying: bool,
  audioRef: ref(option(Dom.element))
};

type action =
  | TogglePlay
  | Next;

let setAudioRef = (theRef, {ReasonReact.state}) =>
  state.audioRef := Js.Nullable.to_opt(theRef);

let component = ReasonReact.reducerComponent("App");

let srcUrl = "https://s3.eu-central-1.amazonaws.com/davidnaas-demo/Gloom+IV.mp3";

let queue = [|
  "https://s3.eu-central-1.amazonaws.com/davidnaas-demo/Phase+locked+fugue.mp3",
  "https://s3.eu-central-1.amazonaws.com/davidnaas-demo/Milky+lemon.mp3",
  "https://s3.eu-central-1.amazonaws.com/davidnaas-demo/Gloom+IV.mp3"
|];

let make = (_children) => {
  ...component,
  initialState: () => {isPlaying: false, audioRef: ref(None), index: 0, queue},
  reducer: (action, state) =>
    switch action {
    | TogglePlay =>
      ReasonReact.UpdateWithSideEffects(
        {
          isPlaying: ! state.isPlaying,
          audioRef: state.audioRef,
          index: state.index,
          queue: state.queue
        },
        (
          ({state: {audioRef, isPlaying}}) =>
            switch audioRef^ {
            | None => ()
            | Some(r) =>
              let audio = ReactDOMRe.domElementToObj(r);
              if (isPlaying) {
                audio##play()
              } else {
                audio##pause()
              }
            }
        )
      )
    },
  render: ({state: {isPlaying, queue, index}, reduce, handle}) =>
    <div className="App">
      <PlayerControls
        isPlaying
        onClickPlay=(reduce((_evt) => TogglePlay))
        onClickNext=(reduce((_evt) => Next))
      />
      <audio ref=(handle(setAudioRef)) src=queue[index] />
    </div>
};
