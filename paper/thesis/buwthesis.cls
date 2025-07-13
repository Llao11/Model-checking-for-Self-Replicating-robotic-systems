%%
%% buwthesis.cls
%% ===============
%%
%% Options (\documentclass[<comma-separated options list>]{buwthesis})
%% ---------------------------------------------------------------------
%% - english      For a thesis written in English
%% - german       For a thesis written in German
%% - bachelor     For a bachelor thesis
%% - master       For a master thesis
%% - project      For a project report
%% Default: [german,bachelor]
%%
%% New commands
%% ------------
%% \ThesisSetTitle{<title>}
%% \ThesisSetSubtitle{<subtitle>} (optional)
%% \ThesisSetKeywords{<comma-and-space-separated list of keywords>} (optional)
%% \ThesisSetAuthor{<your first name> <your last name>}
%% \ThesisSetStudentNumber{<your number>}
%% \ThesisSetDateOfBirth{<dd>}{<mm>}{<yyyy of your birthday>}
%% \ThesisSetPlaceOfBirth{<location you were born>}
%% \ThesisSetProgramme{<degree programme name>}
%% \ThesisSetSupervisors{<comma-separated list of your supervisors>}
%% \ThesisSetSubmissionDate{<dd>}{<mm>}{<yyyy of your final submission>}
%% \ThesisSetLocation{<your current location>} (optional, default: Weimar)
%%   These commands can be used to specify some of the values that are used for
%%   generating the title page, and the declaration of independent work.
%%   Besides the commands marked (optional), all of these have to be specified
%%   before \begin{document} or else compilation will abort.
%%
%% \formatdateshort{<dd>}{<mm>}{<yyyy>}
%%   Analogous to \formatdate{<dd>}{<mm>}{<yyyy>} of the datetime package, but
%%   prints a shorter version to be used in tables or figures.
%%
%% New environments
%% ----------------
%% frontmatter
%%  This will print the title page and the declaration of independent work.
%%  The pagenumbers will be turned to arabic and reset when this environment
%%  ends.
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Required packages:
%% - babel
%% - caption
%% - datetime
%% - fontenc
%% - geometry
%% - ifpdf
%% - ifthen
%% - inputenc
%% - siunitx
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


\def\fileversion{v1.3}
\def\filedate{2014/01/08}
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{buwthesis}[\filedate\space\fileversion]


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Load base class (scrreprt) and basic utilities
\LoadClass[a4paper,12pt,abstract,parskip=half,numbers=noendperiod]{scrreprt}
\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
\RequirePackage{ifpdf}
\RequirePackage{ifthen}
\RequirePackage{siunitx}
\RequirePackage{tikz}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Options

% Language
\newcommand{\documentlanguage}{}
\DeclareOption{english}{%
  \renewcommand{\documentlanguage}{english}%
}
\DeclareOption{german}{%
  \renewcommand{\documentlanguage}{ngerman}%
}
\ExecuteOptions{german} % default

% Type
\newcommand{\thesistype}{}
\DeclareOption{bachelor}{%
  \renewcommand{\thesistype}{Bachelor's Thesis}%
}
\DeclareOption{master}{%
  \renewcommand{\thesistype}{Master's Thesis}%
}
\DeclareOption{project}{%
  \renewcommand{\thesistype}{Project Report}%
}
\ExecuteOptions{bachelor} % default

\ProcessOptions

% Language
\RequirePackage[\documentlanguage]{babel}
% Datetime
% Add ``.'' after abbreviated months
\expandafter\newcommand\csname shortdateperiod1\endcsname{.}
\expandafter\newcommand\csname shortdateperiod2\endcsname{.}
\expandafter\newcommand\csname shortdateperiod3\endcsname{.}
\expandafter\newcommand\csname shortdateperiod4\endcsname{.}
\expandafter\newcommand\csname shortdateperiod5\endcsname{}% May
\expandafter\newcommand\csname shortdateperiod6\endcsname{e}% June
\expandafter\newcommand\csname shortdateperiod7\endcsname{y}% July
\expandafter\newcommand\csname shortdateperiod8\endcsname{.}
\expandafter\newcommand\csname shortdateperiod9\endcsname{.}
\expandafter\newcommand\csname shortdateperiod10\endcsname{.}
\expandafter\newcommand\csname shortdateperiod11\endcsname{.}
\expandafter\newcommand\csname shortdateperiod12\endcsname{.}
\newcommand{\formatdateshort}[3]{{\shortdate\formatdate{#1}{#2}{#3}}}
\ifthenelse{\equal{\documentlanguage}{english}}{%
  \RequirePackage[us,nodayofweek]{datetime}%
  \renewcommand{\formatdateshort}[3]{\shortmonthname[#2]{}\csname shortdateperiod#2\endcsname{}\ #1, #3}%
}{}
\ifthenelse{\equal{\documentlanguage}{ngerman}}{%
  \RequirePackage[nodayofweek]{datetime}%
  \newdateformat{germanlongdate}{\THEDAY.\ \monthname[\THEMONTH]{} \THEYEAR}%
  \germanlongdate%
  %\renewcommand{\dateseparator}{.}%
  \renewcommand{\formatdateshort}[3]{\twodigit{#1}.\twodigit{#2}.#3}%
}{}
% SI units
\sisetup{detect-all,per-mode=symbol}
\ifthenelse{\equal{\documentlanguage}{ngerman}}{%
  \sisetup{locale=DE}%
}{}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Variables
\newtoks\thesistitle
\newcommand{\ThesisSetTitle}[1]{\global\thesistitle{#1}}

\newtoks\thesissubtitle
\newcommand{\ThesisSetSubtitle}[1]{\global\thesissubtitle{#1}}

\newtoks\thesisauthor
\newcommand{\ThesisSetAuthor}[1]{\global\thesisauthor{#1}}

\newtoks\thesissupervisors
\newcommand{\ThesisSetSupervisors}[1]{\global\thesissupervisors{#1}}

\newtoks\thesissubmissiondate
\newcommand{\ThesisSetSubmissionDate}[3]{\global\thesissubmissiondate{\formatdate{#1}{#2}{#3}}}

\newtoks\thesislocation
\newcommand{\ThesisSetLocation}[1]{\global\thesislocation{#1}}
\ThesisSetLocation{Weimar} % default

\newtoks\thesisauthorstudentnumber
\newcommand{\ThesisSetStudentNumber}[1]{\global\thesisauthorstudentnumber{#1}}

\newtoks\thesisauthordateofbirth
\newcommand{\ThesisSetDateOfBirth}[3]{\global\thesisauthordateofbirth{\formatdateshort{#1}{#2}{#3}}}

\newtoks\thesisauthorplaceofbirth
\newcommand{\ThesisSetPlaceOfBirth}[1]{\global\thesisauthorplaceofbirth{#1}}

\newtoks\thesisprogramme
\newcommand{\ThesisSetProgramme}[1]{\global\thesisprogramme{#1}}

\newtoks\thesiskeywords
\newcommand{\ThesisSetKeywords}[1]{\global\thesiskeywords{#1}}

% Check if variables are set
% \checkthesisvariable{variable value}{name}{setter command}{example}
\newcommand{\checkthesisvariable}[4]{%
  \ifthenelse{\equal{#1}{}}{%
    \ClassWarning{buwthesis}{%
      #2 was not defined! %
      Use command "#3{#2}" (e.g.: "#4") before "begin{document}"}%
    \global\thesisvariableerrors{true}%
  }{}%
}
\newcommand{\checkthesisvariabledate}[3]{%
  \ifthenelse{\equal{#1}{}}{%
    \ClassWarning{buwthesis}{%
      #2 was not defined! %
      Use command "#3{day}{month}{year}" (e.g.: "#3{31}{12}{2022}") before "begin{document}"}%
    \global\thesisvariableerrors{true}%
  }{}%
}
% Checking all variables...
\newcommand{\checkthesisvariables}{%
  \newtoks\thesisvariableerrors%
  \checkthesisvariable{\the\thesistitle}{Title}{ThesisSetTitle}{Title of my Thesis}%
  \checkthesisvariable{\the\thesisauthor}{Author}{ThesisSetAuthor}{Given names Last name}%
  \checkthesisvariable{\the\thesissupervisors}{Supervisors}{ThesisSetSupervisors}{Prof. Dr. Bernd Fr\"ohlich,Prof. Dr. Unknown Yet}%
  \checkthesisvariabledate{\the\thesissubmissiondate}{Submission date}{ThesisSetSubmissionDate}%
  \checkthesisvariable{\the\thesisprogramme}{Degree Programme}{ThesisSetProgramme}{Computer Science and Media}%
  \ifthenelse{\equal{\the\thesisvariableerrors}{true}}{%
    \ClassError{buwthesis}{%
      Not all required variables for the thesis template have been set}{%
      See the Warnings for class buwthesis above.}%
  }{}%
}
% ... at the begin of the document
\AtBeginDocument{\checkthesisvariables}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Template words
\newtoks\thesisfrontpagefaculty
\newtoks\thesisfrontpagecourse
\newtoks\thesisfrontpagetypename
\newtoks\thesisfrontpagestudentnumber
\newtoks\thesisfrontpageborn
\newtoks\thesisfrontpagesupervisor
\newtoks\thesisfrontpagedateofsubmission
\newtoks\thesisdeclarationtitle
\newtoks\thesisdeclarationtext
\newtoks\thesisfrontmatterkeywords
\ifthenelse{\equal{\documentlanguage}{english}}{%
  \global\thesisfrontpagefaculty{Faculty of Media}
  \global\thesisfrontpagecourse{Degree Programme }
  \global\thesisfrontpagesupervisor{Referee}
  \global\thesisfrontpagedateofsubmission{Submission date}
  \global\thesisdeclarationtitle{Declaration}
  \global\thesisdeclarationtext{Unless otherwise indicated in the text or %
    references, this thesis is entirely the product of my own scholarly work.}
  \global\thesisfrontmatterkeywords{Keywords}
}{}
\ifthenelse{\equal{\documentlanguage}{ngerman}}{%
  \global\thesisfrontpagefaculty{Fakult\"at Medien}
  \global\thesisfrontpagecourse{Studiengang }
  \global\thesisfrontpagetypename{arbeit}
  \global\thesisfrontpagestudentnumber{Matrikelnummer}
  \global\thesisfrontpageborn{geb. am \the\thesisauthordateofbirth{} in %
    \the\thesisauthorplaceofbirth}
  \global\thesisfrontpagesupervisor{Gutachter}
  \global\thesisfrontpagedateofsubmission{Datum der Abgabe}
  \global\thesisdeclarationtitle{Erkl\"arung}
  \global\thesisdeclarationtext{Hiermit versichere ich, dass ich diese Arbeit %
    selbstst\"andig verfasst und keine anderen als die angegebenen Quellen und %
    Hilfsmittel verwendet habe.}
  \global\thesisfrontmatterkeywords{Schl\"usselworte}
}{}

% Frontpage
\newcommand{\frontpage}{%
  \thispagestyle{empty}
  \begin{titlepage}
		\vspace{2cm}
		\hspace*{-1cm}
    \parbox{10cm}{\normalsize Bauhaus-Universit\"at Weimar\\
      \the\thesisfrontpagefaculty\\
      \the\thesisfrontpagecourse\the\thesisprogramme}

		\begin{center}
			\vspace{3cm}
      {\Huge\bfseries\the\thesistitle}

      {\LARGE\the\thesissubtitle}

      \vspace{3cm}\Huge
      {\bfseries\thesistype}
		\end{center}
    \vspace{\fill}\normalsize
    \the\thesisauthor\hfill\the\thesisfrontpagestudentnumber{} %
      \the\thesisauthorstudentnumber\\%
    \the\thesisfrontpageborn\\[3em]
    \newcounter{supervisors}\makeatletter%
    \@for \name:=\the\thesissupervisors\do{%
      \addtocounter{supervisors}{1}\arabic{supervisors}. %
      \the\thesisfrontpagesupervisor: \name \\%
    }%
    \makeatother\\[3em]%
    \the\thesisfrontpagedateofsubmission: \the\thesissubmissiondate
\tikz [remember picture, overlay] %
\node [shift={(-3cm,5cm)}] at (current page.south east) %
[anchor=south east] %
{\includegraphics[width=4cm]{img/logo_se}};
\tikz [remember picture, overlay] %
\node [shift={(-1cm,-1cm)}] at (current page.north east) %
[anchor=north east] %
{\includegraphics[width=6cm]{img/logo_uni}};

  \end{titlepage}
}%

% Declaration of independent work
\newcommand{\declaration}{
  \begin{titlepage}
    \vspace*{\fill}
    \parindent 0cm
    \begin{center}
      \textbf{\huge \the\thesisdeclarationtitle}
    \end{center}

    \vspace{1cm}

		\large \the\thesisdeclarationtext

    \vspace{1cm}
    \the\thesislocation, \the\thesissubmissiondate

    \vspace{2cm}
    \centering
    \par\noindent\makebox[2.5in]{\hrulefill}%
    \par\noindent\makebox[2.5in]{\the\thesisauthor}

    \vspace*{\fill}
  \end{titlepage}
}

\newenvironment{frontmatter}{%
  \pagenumbering{roman}%
  \frontpage%
  \pagestyle{plain}%
  \declaration%
}{%
  \clearpage%
  \pagenumbering{arabic}%
}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Page layout
\RequirePackage{geometry}
\RequirePackage[automark]{scrlayer-scrpage}

% could be used to change the page geometry but scrreprt's default are fine
% \geometry{body={140mm,210mm},footskip=12mm}


\pagestyle{scrheadings}
\clearpairofpagestyles
\cohead{\headmark}
\cofoot*{\thepage}
\setkomafont{pagehead}{\normalfont\sffamily}
\setkomafont{pagefoot}{\normalfont\sffamily}

% Enumerate subsections and include them in the table of contents
\setcounter{secnumdepth}{2}
\setcounter{tocdepth}{2}

% Specification of figure/table caption style
\RequirePackage[font=small,labelfont=bf]{caption}
