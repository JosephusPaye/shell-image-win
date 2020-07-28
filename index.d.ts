export interface GetImageOptions {
    /**
     * The image width.
     *
     * @default 256
     */
    width?: number;

    /**
     * The image height.
     *
     * @default 256
     */
    height?: number;

    /**
     * The image flags.
     */
    flags?: number;
}

declare namespace shellImageWin {
    /**
     * Get the associated shell image for a given path as a PNG buffer.
     */
    export function getImageForPath(
        filePath: string,
        options: GetImageOptions | undefined,
        callback: (err: String | null, imageBuffer: Buffer) => void,
    ): void;

    /**
     * Get the associated shell image for a given path as a PNG buffer.
     */
    export function getImageForPath(
        filePath: string,
        options: GetImageOptions | undefined,
    ): Promise<Buffer>;

    /**
     * The image extraction flags.
     */
    export namespace flags {
        export const ResizeToFit: number;
        export const BiggerSizeOk: number;
        export const MemoryOnly: number;
        export const IconOnly: number;
        export const ThumbnailOnly: number;
        export const InCacheOnly: number;
        export const CropToSquare: number;
        export const WideThumbnails: number;
        export const IconBackground: number;
        export const ScaleUp: number;
    }
}

export = shellImageWin;
