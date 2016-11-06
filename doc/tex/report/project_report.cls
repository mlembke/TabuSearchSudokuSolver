% !TeX encoding = UTF-8 Unicode
% ******************************************************************************
% Project report class
% ******************************************************************************
% ==============================================================================
% Identification
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{project_report}[2016/04/16 Project report class]
% Preliminary declarations
\newcommand*{\@thisclass}{project_report}
\newcommand*{\@baseclass}{article}
\newcommand*{\VariableNotSetFix}[1]{\texttt{\string#1} currently not set. Please fix this.}

\RequirePackage{etoolbox}
\newtoggle{usebibliography}
\toggletrue{usebibliography}
% ------------------------------------------------------------------------------
% Options
\DeclareOption{oneside}{ \PassOptionsToClass{\CurrentOption}{\@baseclass} }
\DeclareOption{twoside}{ \PassOptionsToClass{\CurrentOption}{\@baseclass} }
\DeclareOption{draft}{ \PassOptionsToClass{\CurrentOption}{\@baseclass} }
\DeclareOption{final}{ \PassOptionsToClass{\CurrentOption}{\@baseclass} }
\DeclareOption{10pt}{ \PassOptionsToClass{\CurrentOption}{\@baseclass} }
\DeclareOption{11pt}{ \PassOptionsToClass{\CurrentOption}{\@baseclass} }
\DeclareOption{12pt}{ \PassOptionsToClass{\CurrentOption}{\@baseclass} }
\DeclareOption{nobibliography}{\togglefalse{usebibliography}}

\DeclareOption{titlepage}%
{\ClassWarning{\@thisclass}{Title page always generated. Option '\CurrentOption' ignored.}}
\DeclareOption{notitlepage}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' not available for '\@thisclass'.}}
\DeclareOption{onecolumn}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' superfluous.  Ignored.}}
\DeclareOption{twocolumn}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' not available for '\@thisclass'.}}
\DeclareOption{landscape}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' not available for '\@thisclass'.}}
\DeclareOption{legalpaper}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' not available for '\@thisclass'.}}
\DeclareOption{openright}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' superfluous.  Ignored.}}
\DeclareOption{openany}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' not available for '\@thisclass'.}}
\DeclareOption{a4paper}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' superfluous.  Ignored.}}
\DeclareOption{a5paper}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' not available for '\@thisclass'.}}
\DeclareOption{executivepaper}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' not available for '\@thisclass'.}}
\DeclareOption{b5paper}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' not available for '\@thisclass'.}}
\DeclareOption{letterpaper}%
{\ClassWarning{\@thisclass}{Option '\CurrentOption' superfluous. Ignored.}}
% Fallback
\DeclareOption*{\ClassWarning{\@thisclass}{Unknown option '\CurrentOption'}}
\ProcessOptions\relax
\LoadClass[10pt,titlepage,a4paper,oneside,final]{\@baseclass}
% ------------------------------------------------------------------------------
% More declarations
\newcommand*{\subtitle}[1]{\newcommand*{\@subtitle}{#1}}
\newcommand*{\supervisor}[1]{\newcommand*{\@supervisor}{#1}}
\newcommand*{\course}[1]{\newcommand*{\@course}{#1}}
\newcommand*{\coursecode}[1]{\newcommand{\@coursecode}{#1}}
\newcommand*{\university}[1]{\newcommand{\@university}{#1}}
\newcommand*{\faculty}[1]{\newcommand{\@faculty}{#1}}

% ------------------------------------------------------------------------------
% Required packages
\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage[MeX]{polski}
\RequirePackage[polish]{babel}
\RequirePackage{indentfirst}
\RequirePackage{geometry}
\RequirePackage{fancyhdr}
%\RequirePackage[Sonny]{fncychap}
\RequirePackage{helvet}
\RequirePackage{csquotes}
\RequirePackage{xpatch}
\RequirePackage{afterpage}
\RequirePackage{mathtools}
\RequirePackage{amsfonts}
\RequirePackage{tikz}
\RequirePackage{booktabs}
\RequirePackage{multirow}
\iftoggle{usebibliography}{%
\RequirePackage[backend=biber,style=authoryear=ibid,maxnames=3]{biblatex}
}{%
}
\RequirePackage{graphicx}
\RequirePackage{float}
\RequirePackage{subfigure}
\RequirePackage[plainpages=false,pdfencoding=unicode]{hyperref}
\RequirePackage[toc,page]{appendix}
% ------------------------------------------------------------------------------
% Packages settings
% Graphics path
\graphicspath{ {./figures/} }

% csquotes settings
\DeclareQuoteStyle{polish} %
{\quotedblbase}{\textquotedblright} %
{\guillemotleft}{\guillemotright}

% geometry settings
\@ifclasswith{\@thisclass}{twoside}{%
	\geometry{%
		a4paper,
		top=25mm,
		bottom=25mm,
		inner=30mm,
		outer=20mm
	}
}{%
	\geometry{%
		a4paper,
		top=25mm,
		bottom=25mm,
		left=25mm,
		right=25mm}
}
% fancyhdr settings
\fancypagestyle{plain}{%
	\fancyhf{}% clear all header and footer fields
	\renewcommand{\headrulewidth}{0pt}%
	\renewcommand{\footrulewidth}{0pt}%
}
\setlength{\headheight}{15pt}
% Style settings
\frenchspacing
%\pagestyle{fancy}

% math commands
\DeclarePairedDelimiter{\norm}{\lVert}{\rVert}
\DeclarePairedDelimiter\abs{\lvert}{\rvert}%

% Other
% Empty pages after \cleardoublepage
\makeatletter
\def\cleardoublepage{\clearpage\if@twoside \ifodd\c@page\else
    \hbox{}\thispagestyle{empty}\newpage\if@twocolumn\hbox{}\newpage\fi\fi\fi}
\makeatother
% ------------------------------------------------------------------------------ 
% Custom titlepage
\makeatletter
\newcommand{\sepline}{\rule{\linewidth}{0.4mm}}
% ------------------------------------------------------------------------------ 
\renewcommand*{\maketitle}{%
	\@ifundefined{@course}{%
		\providecommand*{\@course}{\VariableNotSetFix{\course}}%
		
	}{}
	
	\@ifundefined{@supervisor}{%
		\providecommand*{\@supervisor}{\VariableNotSetFix{\supervisor}}%
	}{}
	\hypersetup{pageanchor=false}
	\begin{titlepage}%
		\vspace*{1cm}
		\begin{center}%
			\@ifundefined{@university}{}{%
			{\small \@university \par}}%
			\@ifundefined{@faculty}{}{%
			{\small \@faculty \par}}%
		\end{center}
		\vspace{1cm}
		\begin{center}%
			\@ifundefined{@coursecode}{%
				{\Large \@course \par}%
			}{%
			{\Large \@course \ (\@coursecode) \par}}%
		\end{center}
		\sepline
		\begin{center}%
			{\LARGE \textsc{\@title} \par}
			\@ifundefined{@subtitle}{}%
			{\vspace{0.5cm}%
				\normalsize --- \textsc{\@subtitle} --- \par}%
		\end{center}
		\sepline
		\vspace{1cm}
		\begin{center}%
			{\normalsize
				\itshape
				\lineskip .5em%
				\begin{tabular}[t]{c}%
					\@author
				\end{tabular}\par}%
		\end{center}		
		\vspace{2cm}
		\begin{flushright}%
			{\normalsize Opiekun projektu: \par}
			{\normalsize \itshape \@supervisor \par}
		\end{flushright}		
		\vfill\null
		\begin{center}%
			\@date
		\end{center}
		\@thanks
	\end{titlepage}%
	\hypersetup{pageanchor=true}
	\setcounter{footnote}{0}%
	\global\let\thanks\relax
	\global\let\maketitle\relax
	\global\let\@thanks\@empty
	\global\let\@author\@empty
	\global\let\@date\@empty
	\global\let\@title\@empty
	\global\let\title\relax
	\global\let\author\relax
	\global\let\date\relax
	\global\let\and\relax
	
}

\makeatother
% ******************************************************************************
