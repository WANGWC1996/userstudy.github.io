import React from "react";
import { connect } from "react-redux";
import classNames from "classnames";
import { setActiveComponent, restart } from "../actions";
import Histogram from "./Histogram";

class Result extends React.Component {
  constructor(props) {
    super(props);
    this.ths = [];
    this.props.attributes.forEach(([attr, config]) => {
      if (this.props.mask[attr]) {
        const th = <th key={attr}>{attr}</th>;
        this.ths.push(th);
      }
    });
    this.ths.push(<th key="chooseCheckbox"/>);

    //ranked points withpoints and ranking
    this.pointsScoreRanking = [];
    for(let i = 0; i < this.props.leftPoints.length; ++i)
    {
      let pt = [], index = this.props.leftPoints[i];
      for(let j = 0; j < this.props.candidates[index].length; ++j)
        pt.push(this.props.candidates[index][j]);
      pt.push(this.props.scores[i]);
      pt.push(i+1);
      this.pointsScoreRanking.push(pt);
    }

    //ranked points in html
    this.trs = this.props.leftPoints.map((idx, i) => (
        <tr key={i} data-toggle="tooltip" title={this.props.labels[idx]}>
          {this.props.candidates[idx].map((x, j) => (
              <td key={j}>{x}</td>
          ))}
          <td key="chooseCheckbox"/>
        </tr>
    ));

    //points for presenting
    const top = [this.trs[0]];
    const top1small = [], top1large = [];
    for (let i = 1; i < this.props.leftPoints.length; ++i)
    {
      if ((this.props.scores[0] - this.props.scores[i]) / this.props.scores[0] < 0.1)
        top1small.push(this.pointsScoreRanking[i]);
      else
        top1large.push(this.pointsScoreRanking[i]);
    }
    const top1smallSample = this.pickRandom(top1small, 5);
    const top1largeSample = this.pickRandom(top1large, 5);
    for (let i = 0; i < top1largeSample.length; ++i)
      top1smallSample.push(top1largeSample[i]);

    const present = [];
    for(let i = 0; i < this.props.leftPoints.length; ++i)
    {
      present.push(this.pointsScoreRanking[i].map((x, j) => { return (x); }));
      present.push("\n");
    }

    let checkboxValues = {};
    for (let i = 0; i < 10; i++) {
      checkboxValues[`myCheckbox${i}`] = false;
    }

    this.state = {
      intro: "Here is your favorite car.",
      inst: "Please compare your favorite car and the following cars and indicate if you are interested in the following cars?",
      ths: this.ths,
      top: top,
      topSample: top1smallSample,
      output: present,
      checkboxValues: checkboxValues
    };


  }

  pickRandom = (arr, n) => {
    const arrCopy = [...arr];
    if (arrCopy.length <= n)
      return arrCopy;
    // Shuffle array
    for (let i = arrCopy.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [arrCopy[i], arrCopy[j]] = [arrCopy[j], arrCopy[i]]; // ES6 array element swap
    }
    return arrCopy.slice(0, n);
  };

  handleCheckboxChange(event) {
    const { id, checked } = event.target;
    this.setState(prevState => ({
      checkboxValues: {
        ...prevState.checkboxValues,
        [id]: checked
      }
    }));
    console.log(this.state.checkboxValues);
  }

  downloadFile = index => {
    if (index === 1) {
      //output
      this.setState(prevState => ({
        output: [
          ...prevState.output,
          "\n\n\n\nTOP-1\n\n",
          ...this.state.topSample.map((item, i) => [
            item.map(x => x),
            prevState.checkboxValues[`myCheckbox${i}`],
            "\n",
          ]),
        ]
      }), () => {
        console.log(this.state.checkboxValues); // Now this will log the updated state
      });

      let checkboxValues = {};
      for (let i = 0; i < 10; i++) {
        checkboxValues[`myCheckbox${i}`] = false;
      }
      this.setState({
        checkboxValues: checkboxValues
      });

      //top-5 points
      const top5 = [];
      for(let i = 0; i < 5; ++i)
        top5.push(this.trs[i]);
      //obtain the index
      const top5small = [], top5large = [];
      for (let i = 5; i < this.props.leftPoints.length; ++i) {
        if ((this.props.scores[4] - this.props.scores[i]) / this.props.scores[4] < 0.1)
          top5small.push(this.pointsScoreRanking[i]);
        else
          top5large.push(this.pointsScoreRanking[i]);
      }
      const top5smallSample = this.pickRandom(top5small, 5);
      const top5largeSample = this.pickRandom(top5large, 5);
      for (let i = 0; i < top5largeSample.length; ++i)
        top5smallSample.push(top5largeSample[i]);
      this.setState({
        intro: "Here are your top-5 favorite cars.",
        inst: "Please compare your favorite top-5 cars and the following cars \n and indicate if you are interested in the following cars?",
        top: top5,
        topSample: top5smallSample
      });
    }
    else if(index === 5) {
      //output
      this.state.output.push("\n\n\n\nTOP-5\n\n")
      for(let i = 0; i < this.state.topSample.length; ++i)
      {
        this.state.output.push(this.state.topSample[i].map(x => { return (x); }));
        this.state.output.push(this.state.checkboxValues[`myCheckbox${i}`]); //preferred default
        this.state.output.push("\n");
      }
      let checkboxValues = {};
      for (let i = 0; i < 10; i++) {
        checkboxValues[`myCheckbox${i}`] = false;
      }
      this.setState({
        checkboxValues: checkboxValues
      });

      //top-10 points
      const top10 = [];
      for (let i = 0; i < 10; ++i)
        top10.push(this.trs[i]);
      //obtain the index
      const top10small = [], top10large = [];
      for (let i = 10; i < this.props.leftPoints.length; ++i)
      {
        if ((this.props.scores[9] - this.props.scores[i]) / this.props.scores[9] < 0.1)
          top10small.push(this.pointsScoreRanking[i]);
        else
          top10large.push(this.pointsScoreRanking[i]);
      }
      const top10smallSample = this.pickRandom(top10small, 5);
      const top10largeSample = this.pickRandom(top10large, 5);
      for (let i = 0; i < top10largeSample.length; ++i)
        top10smallSample.push(top10largeSample[i]);
      this.setState({
        intro: "Here are your top-10 favorite cars.",
        inst: "Please compare your favorite top-10 cars and the following cars \n and indicate if you are interested in the following cars?",
        top: top10,
        topSample: top10smallSample
      });
    }
    else
    {
      //output
      this.state.output.push("\n\n\n\nTOP-10\n\n")
      for(let i = 0; i < this.state.topSample.length; ++i)
      {
        this.state.output.push(this.state.topSample[i].map(x => { return (x); }));
        this.state.output.push(this.state.checkboxValues[`myCheckbox${i}`]); //preferred default
        this.state.output.push("\n");
      }

      let blob = new Blob([this.state.output], {type: 'text/plain'});
      let url = URL.createObjectURL(blob);
      let downloadLink = document.createElement('a');
      downloadLink.href = url;
      downloadLink.download = 'sample.txt'; // 指定下载文件及类型
      document.body.appendChild(downloadLink);
      downloadLink.click();
      document.body.removeChild(downloadLink);
      this.props.showEnd();
    }
  };

  render() {
    const topPresentwithbox = this.state.topSample.map((idx, i) => (
        <tr key={i} data-toggle="tooltip" title={this.props.labels[idx]}>
          <td key={0}>{idx[0]}</td>
          <td key={1}>{idx[1]}</td>
          <td key={2}>{idx[2]}</td>
          <td key={3}>{idx[3]}</td>
          <td>
            <input
                type="checkbox"
                id={`myCheckbox${i}`}
                name={`myCheckbox${i}`}
                onChange={this.handleCheckboxChange.bind(this)}
                checked={this.state.checkboxValues[`myCheckbox${i}`]}
            />
          </td>
        </tr>
    ));

    return (
        <div>
          <div className="justify-content-center">
            <h4>{this.state.intro}</h4>
            <table className={classNames("table", "table-hover", {
                     "table-fixed": this.trs.length > 7
                   })}
                   style={{
                     maxWidth: "40rem",
                     margin: "auto"
                   }}>
              <thead>
              <tr>{this.ths}</tr>
              </thead>
              <tbody>{this.state.top}</tbody>
            </table>
            <br></br>
            <h5>{this.state.inst}</h5>
            <table
                className={classNames("table", "table-hover", {
                  "table-fixed": this.trs.length > 7
                })}
                style={{
                  maxWidth: "40rem",
                  margin: "auto"
                }}
            >
              <thead>
              <tr>{this.ths}</tr>
              </thead>
              <tbody>{topPresentwithbox}</tbody>
            </table>
            <br></br>
            <div>
              <button
                  type="button"
                  className="btn btn-primary"
                  style={{width: "8rem"}}
                  onClick={() => this.downloadFile(this.state.top.length)}>
                Finish
              </button>
            </div>
          </div>
        </div>
    );
  }
}

const mapStateToProps = ({
  labels,
  candidates,
  leftPoints,
  attributes,
  mask,
  numLeftPoints,
  scores
}) => ({
  labels,
  candidates,
  leftPoints,
  attributes,
  mask,
  numLeftPoints,
  scores
});

const mapDispatchToProps = dispatch => ({
  showEnd: () => {
    dispatch(setActiveComponent("End"));
    dispatch(restart());
  }
});

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(Result);
