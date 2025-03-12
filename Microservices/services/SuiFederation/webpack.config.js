const path = require('path');

module.exports = {
    entry: {
        bridge: './Features/SuiApi/ts/bridge.ts',
        models: './Features/SuiApi/ts/models.ts',
        utils: './Features/SuiApi/ts/utils.ts'
    },
    target: 'node',
    module: {
        rules: [
            {
                test: /\.ts$/,
                use: 'ts-loader',
                exclude: /node_modules/,
            },
        ],
    },
    resolve: {
        extensions: ['.ts', '.js'],
    },
    output: {
        filename: '[name].js',
        path: path.resolve(__dirname, 'js'),
        libraryTarget: 'commonjs2',
    },
    optimization: {
        usedExports: true,
    },
    mode: "production"
};