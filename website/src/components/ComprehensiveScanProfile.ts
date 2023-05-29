import {ScanProfile} from "boot/api/api";

export class ComprehensiveScanProfile {
  'name': string;
  'crossExecution': boolean;
  'brightness': number[];
  'scanTimes': number[];
  'scanInterval': number[];

  constructor() {
    this.name = '';
    this.crossExecution = false;
    this.brightness = [];
    this.scanTimes = [];
    this.scanInterval = [];
  }

  toScanProfile() :ScanProfile[] {
    if (this.crossExecution) {
      const scanProfiles: ScanProfile[] = [];
      for (const bri of this.brightness) {
        for (const sct of this.scanTimes) {
          for (const sci of this.scanInterval) {
            scanProfiles.push({
              brightness: bri,
              scanTimes: sct,
              scanInterval: sci,
            });
          }
        }
      }
      return scanProfiles;
    } else {
      return [{
        brightness: this.brightness[0],
        scanTimes: this.scanTimes[0],
        scanInterval: this.scanInterval[0],
      }]
    }
  }
}
